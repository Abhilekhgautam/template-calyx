import json

WIDTH = 80
HEIGHT = 60
TOTAL_PIXELS = WIDTH * HEIGHT  # 4800

# Generate sequential pixels: 0, 1, 2, ... 4799
# Pixel at (row, col) has value = row * 80 + col
pixels = [row * WIDTH + col for row in range(HEIGHT) for col in range(WIDTH)]

data = {
    "img": {
        "data": pixels,
        "format": {
            "numeric_type": "bitnum",
            "is_signed": False,
            "width": 32
        }
    }
}

# Write out to data.json
with open("data.json", "w") as f:
    json.dump(data, f, indent=2)

print(f"Successfully generated data.json with {TOTAL_PIXELS} pixels!")
