from PIL import Image
import os

def png_to_xpm(input_file, output_file):
    with Image.open(input_file) as img:
        # Ensure the image is in RGB mode
        img = img.convert("RGB")

        # Get image dimensions
        width, height = img.size
        pixels = img.load()

        # Create color map
        colors = {}
        color_index = 0
        xpm_data = []

        for y in range(height):
            row = []
            for x in range(width):
                rgb = pixels[x, y]
                if rgb not in colors:
                    color_key = chr(65 + color_index)  # Use ASCII characters A-Z for colors
                    colors[rgb] = color_key
                    color_index += 1
                row.append(colors[rgb])
            xpm_data.append('"' + "".join(row) + '"')

        # Write the XPM file
        with open(output_file, "w") as f:
            # XPM header
            f.write("/* XPM */\n")
            f.write("static char *image[] = {\n")
            f.write(f'"{width} {height} {len(colors)} 1",\n')

            # Color definitions
            for rgb, key in colors.items():
                hex_color = f"#{rgb[0]:02x}{rgb[1]:02x}{rgb[2]:02x}"
                f.write(f'"{key} c {hex_color}",\n')

            # Pixel data
            f.write(",\n".join(xpm_data))
            f.write("\n};\n")

        print(f"Converted {input_file} -> {output_file}")

# Input and output directories
input_dir = "./png_files"
output_dir = "./xpm_files"
os.makedirs(output_dir, exist_ok=True)


for filename in os.listdir(input_dir):
    if filename.endswith(".png"):
        png_path = os.path.join(input_dir, filename)
        xpm_path = os.path.join(output_dir, filename.replace(".png", ".xpm"))
        png_to_xpm(png_path, xpm_path)