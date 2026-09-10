import json

# --- Dimensions ---
WIDTH = 80
HEIGHT = 60
PIXELS_PER_CHANNEL = WIDTH * HEIGHT  # 4,800
TOTAL_IMAGE_WORDS = PIXELS_PER_CHANNEL * 3  # 14,400 (RGB)

NUM_FILTERS = 8
CHANNELS = 3
KERNEL_TAPS = 5 * 5  # 25
TOTAL_WEIGHTS = NUM_FILTERS * CHANNELS * KERNEL_TAPS  # 600

TOTAL_OUTPUT_WORDS = NUM_FILTERS * PIXELS_PER_CHANNEL  # 38,400

# --------------------------------------------------------------------------
# 1. Generate Image (14,400 elements in Planar NCHW order)
# --------------------------------------------------------------------------
# Red:   values 1
# Green: values 2
# Blue:  values 3
# (Or change to sequential numbers if you prefer: [i for i in range(14400)])
red_channel   = [1 for _ in range(PIXELS_PER_CHANNEL)]
green_channel = [2 for _ in range(PIXELS_PER_CHANNEL)]
blue_channel  = [3 for _ in range(PIXELS_PER_CHANNEL)]

img_data = red_channel + green_channel + blue_channel

# --------------------------------------------------------------------------
# 2. Generate Weights (600 elements)
# --------------------------------------------------------------------------
# We set all weights to 1 for easy debugging in Cider!
# For a 5x5 window of 1s:
# Red Conv = 25 * 1 = 25
# Green Conv = 25 * 2 = 50
# Blue Conv = 25 * 3 = 75
# Expected final_pixel = 25 + 50 + 75 = 150!
weights_data = [1 for _ in range(TOTAL_WEIGHTS)]

# --------------------------------------------------------------------------
# 3. Output Memory Buffer (38,400 zeros)
# --------------------------------------------------------------------------
# Cider requires external memories to be defined in JSON even if only written to
out_mem_data = [0 for _ in range(TOTAL_OUTPUT_WORDS)]

# --------------------------------------------------------------------------
# Build Cider JSON Structure
# --------------------------------------------------------------------------
data = {
    "img": {
        "data": img_data,
        "format": {
            "numeric_type": "bitnum",
            "is_signed": False,
            "width": 32
        }
    },
    "weights": {
        "data": weights_data,
        "format": {
            "numeric_type": "bitnum",
            "is_signed": False,
            "width": 32
        }
    },
    "out_mem": {
        "data": out_mem_data,
        "format": {
            "numeric_type": "bitnum",
            "is_signed": False,
            "width": 32
        }
    }
}

with open("data.json", "w") as f:
    json.dump(data, f, indent=2)

print("Generated data.json successfully:")
print(f" - img:     {len(img_data)} elements")
print(f" - weights: {len(weights_data)} elements")
print(f" - out_mem: {len(out_mem_data)} elements")
