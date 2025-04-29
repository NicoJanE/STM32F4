#!/bin/bash

# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
# USAGE
# - `./make_graph.sh all`                 Displays all include files
# - `./make_graph header <filename.h>`    Displays where the include is used
# - `./make_graph file <filename.cpp|c`   Displays all includes of the file`



# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
# Configuration
#
ROOT_DIR=$(dirname "$(realpath "$0")")/..
SRC_DIR=${SRC_DIR:-"../src"}  # Adjust SRC_DIR to the source directory
CURRENT_DIR=$(pwd)
OUT_DOT="$CURRENT_DIR/includes.dot"
OUT_SVG="$CURRENT_DIR/include-graph.svg"
# echo -e "SVG PATH: $OUT_SVG\n\n"

# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
# Function to generate the graph showing where a specific header file is included
#
generate_header_includes() {
  if [ -z "$2" ]; then
    echo "Please provide a header file name."
    exit 1
  fi
  header_file="$2"
  echo -e "\tACTION: Generating graph showing where '$header_file' is included...\n"
  echo "digraph includes {" > "$OUT_DOT"
  echo "  node [shape=box];" >> "$OUT_DOT"

  # Use basename to handle just the file name without the path
  header_basename=$(basename "$header_file")
  
  # Debugging: Log header to check
  #echo "Looking for '#include \"$header_basename\"' in files..."
  

  # Find all relevant source files recursively (.cpp, .c, .h, .hpp)
  find "$ROOT_DIR" -type f \( -iname "*.cpp" -o -iname "*.c" -o -iname "*.h" -o -iname "*.hpp" \) | while read -r file; do
    echo "Checking file: $file"
    
    # Display the include path we're looking for
    # echo "Checking for #include \"$header_basename\" in file: $file"
    echo "Checking for #include \"$header_basename\""

    # Debugging: Print the grep command we're running
    grep_cmd="grep -qE '#include\s+[\"<](.+/)*$header_basename[\">]' \"$file\""
    #echo "Running grep command: $grep_cmd"

    # Check if the header is included, including subdirectories in the include path
    if eval "$grep_cmd"; then
      echo -e  "\tFOUND '$header_basename' found in file: $file"
      echo "  \"$file\" -> \"$header_basename\";" >> "$OUT_DOT"
#    else
#      echo "Header '$header_basename' NOT found in file: $file"
    fi
  done

  echo "}" >> "$OUT_DOT"
}

# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
# Function to generate a basic include graph for all header files in the project
#
generate_all_includes() {
  echo "Generating graph for all header includes:"
  echo "digraph includes {" > "$OUT_DOT"
  echo "  node [shape=box];" >> "$OUT_DOT"

  # Find all relevant source files recursively (.cpp, .c, .h, .hpp) in SRC_DIR and its subdirectories
  find "$ROOT_DIR" -type f \( -iname "*.cpp" -o -iname "*.c" -o -iname "*.h" -o -iname "*.hpp" \) | while read -r file; do
    echo "Checking file: $file"
    
    # Look for all #include statements
    grep -oE '#include\s+[\"<](.+/)*([^\">]+)[\">]' "$file" | while read -r include; do
      header_basename=$(basename "$include" | sed 's/[<>"]//g')  # Strip extra characters like quotes and angle brackets
      echo "  \"$file\" -> \"$header_basename\";" >> "$OUT_DOT"
    done
  done

  echo "}" >> "$OUT_DOT"
}

# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
# Function to generate the graph showing headers included by a specific C or C++  file
#
generate_file_includes() {
  if [ -z "$2" ]; then
    echo "Please provide a source file name."
    exit 1
  fi

  source_file="$2"
  echo "Generating graph showing headers included by '$source_file'..."

  # Check if the source file exists in the src directory or its subdirectories
  source_file_path=$(find "$SRC_DIR" -type f -name "$source_file" 2>/dev/null | head -n 1)
  if [ -z "$source_file_path" ]; then
    echo "Source file '$source_file' not found in '$SRC_DIR'."
    exit 1
  fi

  echo "Found '$source_file' at: $source_file_path"

  echo "digraph includes {" > "$OUT_DOT"
  echo "  node [shape=box];" >> "$OUT_DOT"

  # Function to process includes recursively
  process_includes() {
    local file="$1"

    echo "Processing file: $file"

    # Extract all the headers included in this file
    grep -oP '#include\s+["<]\K[^">]+' "$file" | while read -r header; do
      # For each header, create an edge in the graph
      echo "  \"$file\" -> \"$header\";" >> "$OUT_DOT"
      
      # If the header is a file in the source directory, process it recursively
      header_path=$(find "$SRC_DIR" -type f -name "$header" 2>/dev/null | head -n 1)
      if [ -n "$header_path" ] && [ "$header_path" != "$file" ]; then
        process_includes "$header_path"
      fi
    done
  }

  # Start processing the given source file
  process_includes "$source_file_path"

  echo "}" >> "$OUT_DOT"
}

# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
# Main logic to decide what to do based on user arguments
#
if [ -z "$1" ]; then
  echo "Usage: $0 {header|all|file} [header_file|source_file]"
  echo "  header     - Generate graph where specific header is included"
  echo "  all        - Generate a graph for all includes"
  echo "  file       - Generate graph for a specific source file"
  exit 1
fi

# Handle different options
case "$1" in
  "header")
    generate_header_includes "$@"
    ;;
  "all")
    generate_all_includes
    ;;
  "file")
    generate_file_includes "$@"
    ;;
  *)
    echo "Invalid option. Usage: $0 {header|all|file}"
    exit 1
    ;;
esac

# Generate the SVG
# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
echo "- Generating SVG from DOT..."
dot -Tsvg "$OUT_DOT" -o "$OUT_SVG"
echo "- SVG generated at: $OUT_SVG"
echo


# Open it in live server (VSC extension: ritwickdey.LiveServer )
# ✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨
#xdg-open http://127.0.0.1:5500/src_doc/include-graph.svg

SVG_FILE="src_doc/include-graph.svg"
LIVE_SERVER_URL="http://127.0.0.1:5500/$SVG_FILE"

echo -e "AUTOMATICALLY OPENING $LIVE_SERVER_URL in your browser..."
echo "Please make sure Live Server is running!"

# Try to open it in the default web browser
xdg-open $LIVE_SERVER_URL || echo "Unable to open browser automatically. Please open $LIVE_SERVER_URL manually."
echo -e  "\n\nWHEN AUTOMATIC  LOADING FAILED USE **CTRL** AND CLICK HER:  $LIVE_SERVER_URL\n\n\n"