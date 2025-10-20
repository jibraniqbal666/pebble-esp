#!/usr/bin/env python3
"""
ESP32 Build Bridge - Integrates WAF build system with ESP-IDF

This script bridges between Pebble's WAF build system and ESP32's ESP-IDF build system.
It collects Pebble OS source files and generates ESP-IDF components, then calls idf.py.
"""

import os
import sys
import json
import shutil
import subprocess
from pathlib import Path

class ESP32BuildBridge:
    def __init__(self, project_root):
        self.project_root = Path(project_root)
        self.esp32_dir = self.project_root / "platform" / "esp32c3" / "boot"
        self.components_dir = self.esp32_dir / "components"
        self.pebble_fw_dir = self.project_root / "src" / "fw"
        
    def generate_pebble_component(self, source_files, include_dirs, defines):
        """Generate ESP-IDF component from Pebble OS sources"""
        print("Generating Pebble firmware component...")
        
        # Create component directory
        component_dir = self.components_dir / "pebble_fw"
        component_dir.mkdir(parents=True, exist_ok=True)
        
        # Generate CMakeLists.txt for Pebble component
        cmake_content = self._generate_cmake_lists(source_files, include_dirs, defines)
        
        with open(component_dir / "CMakeLists.txt", "w") as f:
            f.write(cmake_content)
            
        # Create source symlinks or copies
        self._setup_source_files(component_dir, source_files)
        
        print(f"Generated component at: {component_dir}")
        
    def _generate_cmake_lists(self, source_files, include_dirs, defines):
        """Generate CMakeLists.txt content for Pebble component"""
        
        # Convert absolute paths to relative paths from component
        rel_sources = []
        for src in source_files:
            src_path = Path(src)
            if src_path.is_absolute():
                try:
                    rel_path = src_path.relative_to(self.project_root)
                    rel_sources.append(f"../../{rel_path}")
                except ValueError:
                    # If can't make relative, copy the file
                    rel_sources.append(src_path.name)
            else:
                rel_sources.append(src)
        
        # Convert include directories
        rel_includes = []
        for inc in include_dirs:
            inc_path = Path(inc)
            if inc_path.is_absolute():
                try:
                    rel_path = inc_path.relative_to(self.project_root)
                    rel_includes.append(f"../../{rel_path}")
                except ValueError:
                    rel_includes.append(str(inc_path))
            else:
                rel_includes.append(inc)
        
        cmake_content = f'''# Auto-generated CMakeLists.txt for Pebble OS component
set(COMPONENT_SRCS
{self._format_cmake_list(rel_sources, 4)}
)

set(COMPONENT_ADD_INCLUDEDIRS
{self._format_cmake_list(rel_includes, 4)}
)

# Pebble OS specific defines
set(COMPONENT_COMPILE_DEFINITIONS
{self._format_cmake_list([f'"{d}"' for d in defines], 4)}
)

# ESP32 compatibility layer
set(COMPONENT_REQUIRES 
    driver 
    freertos 
    esp_system 
    esp_common
    soc
    hal
    log
)

register_component()

# Set C standard for compatibility
target_compile_features(${{COMPONENT_LIB}} PUBLIC c_std_99)

# Add ESP32-specific compile flags for Pebble compatibility
target_compile_options(${{COMPONENT_LIB}} PRIVATE
    -Wno-error=unused-function
    -Wno-error=unused-variable
    -Wno-error=format
    -ffunction-sections
    -fdata-sections
)
'''
        return cmake_content
    
    def _format_cmake_list(self, items, indent=0):
        """Format a list for CMakeLists.txt"""
        if not items:
            return ""
        
        indent_str = " " * indent
        formatted_items = []
        for item in items:
            formatted_items.append(f"{indent_str}{item}")
        
        return "\n".join(formatted_items)
    
    def _setup_source_files(self, component_dir, source_files):
        """Setup source files in component directory (symlinks or copies)"""
        src_dir = component_dir / "src"
        src_dir.mkdir(exist_ok=True)
        
        # For now, we'll rely on relative paths in CMakeLists.txt
        # In the future, we could create symlinks here if needed
        pass
    
    def call_idf_build(self, board="esp32c3", target="build"):
        """Call ESP-IDF build system"""
        print(f"Calling ESP-IDF build for {board}...")
        
        # Change to ESP32 directory
        original_cwd = os.getcwd()
        os.chdir(self.esp32_dir)
        
        try:
            # Set target if needed
            if not (self.esp32_dir / "sdkconfig").exists():
                print(f"Setting ESP-IDF target to {board}...")
                subprocess.run(["idf.py", "set-target", board], check=True)
            
            # Build
            print("Building with ESP-IDF...")
            result = subprocess.run(["idf.py", target], check=True)
            
            print("ESP-IDF build completed successfully!")
            return True
            
        except subprocess.CalledProcessError as e:
            print(f"ESP-IDF build failed: {e}")
            return False
        finally:
            os.chdir(original_cwd)
    
    def create_partition_table(self):
        """Create ESP32 partition table for Pebble OS"""
        partition_content = """# Pebble OS Partition Table
# Name,   Type, SubType, Offset,   Size,    Flags
nvs,      data, nvs,     0x9000,   0x4000,
otadata,  data, ota,     0xd000,   0x2000,
phy_init, data, phy,     0xf000,   0x1000,
ota_0,    app,  ota_0,   0x10000,  0x140000,
ota_1,    app,  ota_1,   0x150000, 0x140000,
storage,  data, fat,     0x290000, 0x100000,
"""
        
        partition_file = self.esp32_dir / "partitions.csv"
        with open(partition_file, "w") as f:
            f.write(partition_content)
        
        print(f"Created partition table: {partition_file}")


def main():
    if len(sys.argv) < 2:
        print("Usage: esp32_build_bridge.py <command> [args...]")
        print("Commands:")
        print("  generate-component <sources.json> - Generate ESP-IDF component from sources")
        print("  build [board] - Build with ESP-IDF")
        print("  flash [board] - Flash with ESP-IDF") 
        print("  partition - Create partition table")
        sys.exit(1)
    
    # Find project root (where wscript is located)
    current_dir = Path(__file__).parent.parent
    
    bridge = ESP32BuildBridge(current_dir)
    command = sys.argv[1]
    
    if command == "generate-component":
        if len(sys.argv) < 3:
            print("Usage: generate-component <sources.json>")
            sys.exit(1)
            
        with open(sys.argv[2], 'r') as f:
            build_info = json.load(f)
        
        bridge.generate_pebble_component(
            build_info.get('sources', []),
            build_info.get('includes', []),
            build_info.get('defines', [])
        )
        
    elif command == "build":
        board = sys.argv[2] if len(sys.argv) > 2 else "esp32c3"
        bridge.call_idf_build(board, "build")
        
    elif command == "flash":
        board = sys.argv[2] if len(sys.argv) > 2 else "esp32c3"
        bridge.call_idf_build(board, "flash")
        
    elif command == "partition":
        bridge.create_partition_table()
        
    else:
        print(f"Unknown command: {command}")
        sys.exit(1)


if __name__ == "__main__":
    main()
