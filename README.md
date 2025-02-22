# Image Editor - C Project

## 📄 Overview
This project is a C-based image editor that supports essential image processing operations such as loading, selecting, cropping, rotating, applying filters, equalizing, and saving images. The editor utilizes two main data structures:

- **`Pixel`**: Stores the RGB values of each pixel.
- **`Details`**: Contains metadata and additional information related to the image.

---

## 🚀 Features and Functionality

### 1️⃣ Load
- Identifies the file type and color properties (grayscale or RGB).
- Loads the image into a two-dimensional pixel array.
- Returns `-1` if the file cannot be loaded.

### 2️⃣ Select
- Selects the entire image with `ALL` or a custom region using coordinates (`x1 y1 x2 y2`).
- Converts input strings to integers using `atoi()`.
- Validates coordinates and retains the previous selection if invalid.

### 3️⃣ Crop
- Crops the image based on the selected region.
- Frees memory associated with the previous image.

### 4️⃣ Rotate
- Rotates the selected region or entire image by a specified angle.
- Handles rotation by transposing the matrix and reversing columns.
- For selection-based rotation, the selection must be square.
- Supports negative angle rotation by converting to positive equivalents.

### 5️⃣ Apply Filter
- Verifies sufficient neighboring pixels for filtering.
- Applies predefined filters using corresponding matrices.

### 6️⃣ Save
- Saves the image in text (`ascii`) or binary format.
- Writes auxiliary information followed by pixel data.
- Rounds pixel values when converting from `double` to `unsigned char`.

### 7️⃣ Equalize
- Computes the frequency of each pixel value.
- Enhances image contrast via histogram equalization.
- Applies the transformation using the calculated new pixel values.

### 8️⃣ Exit
- Releases dynamically allocated memory.
- Closes the program safely.

---

## 🛠️ Usage

### 🔧 Compile the Code
```bash
gcc -o image_editor image_editor.c -lm
```

### 💻 Run the Program
```bash
./image_editor
```

### 📝 Available Commands
```plaintext
LOAD <filename>                # Load an image file
SELECT <x1> <y1> <x2> <y2>     # Select a region
SELECT ALL                     # Select the entire image
CROP                           # Crop the selected region
ROTATE <angle>                 # Rotate the image/selection
APPLY <filter>                 # Apply a filter
EQUALIZE                       # Equalize image histogram
SAVE <filename> [ascii|binary] # Save the image
EXIT                           # Exit the program
```

---

## ⚡ Error Handling
- Handles invalid file formats and unreadable files.
- Validates selection coordinates and image dimensions.
- Ensures proper memory management to avoid leaks.

