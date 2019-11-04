import tensorflow as tf
from tensorflow import keras
import os

print('TensorFlow version: ', tf.__version__)

MODEL_1 = r"Model_M1/Model_M1.h5"
MODEL_2 = r"Model_M2/Model_M2.h5"
MODEL_3 = r"Model_M3/Model_M3.h5"

# Load the .h5 models so that we can convert them to .pb
m1 = keras.models.load_model(MODEL_1, compile=False)
m2 = keras.models.load_model(MODEL_2, compile=False)
m3 = keras.models.load_model(MODEL_3, compile=False)

# Saves the model as .pb at the indicated folder
# Creates a new subdirectory for each new version
# Note: for multiple versions, the server uses the newest version by default
#		but caller can specify version to use
def save_model(model, folderpath, version=1):
	export_path = os.path.join(folderpath, str(version))
	if os.path.isdir(export_path):
	  print('WARNING: Possibly overwriting another model\n')
	tf.keras.experimental.export_saved_model(model, export_path)
	print('\nSaved a model at ', export_path)
	return

save_model(m1, 'Model_M1')
save_model(m2, 'Model_M2')
save_model(m3, 'Model_M3')

# PATH_2 = "Model_M2"
# version = 1
# export_path = os.path.join(PATH_2, str(version))
# print('export_path= {}\n'.format(export_path))
# if os.path.isdir(export_path):
# print('WARNING: Possibly overwriting another model\n')

# tf.keras.experimental.export_saved_model(m2, export_path)

# print('\nSaved Model_M2 at ', export_path)