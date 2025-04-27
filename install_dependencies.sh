#!/bin/bash

echo "Installing Python dependencies..."
pip install -r requirements.txt

echo "Checking if dependencies were installed correctly:"
python -c "import numpy; print('numpy version:', numpy.__version__)"
python -c "import pandas; print('pandas version:', pandas.__version__)"
python -c "import matplotlib; print('matplotlib version:', matplotlib.__version__)"

echo "All dependencies installed successfully!" 