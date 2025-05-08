from PIL import Image

# Load and convert your image
img = Image.open("input.png").convert("L")  # Convert to grayscale
img = img.resize((64, 64), Image.BICUBIC)

# Save as raw binary (no header)
with open("image.raw", "wb") as f:
    f.write(img.tobytes())
