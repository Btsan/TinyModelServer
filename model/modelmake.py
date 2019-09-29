import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv3D
from tensorflow.keras.layers import ConvLSTM2D
from tensorflow.keras.layers import BatchNormalization
import numpy as np
import os
import subprocess

model = Sequential()
model.add(ConvLSTM2D(filters=64, kernel_size=(3, 3), input_shape=(None, 35, 40, 1), padding='same', return_sequences=True, use_bias=True))
model.add(BatchNormalization())

model.add(ConvLSTM2D(filters=64, kernel_size=(3, 3), padding='same', return_sequences=True, use_bias=True))
model.add(BatchNormalization())

model.add(ConvLSTM2D(filters=64, kernel_size=(3, 3), padding='same', return_sequences=True, use_bias=True))
model.add(BatchNormalization())

model.add(ConvLSTM2D(filters=64, kernel_size=(3, 3), padding='same', return_sequences=True, use_bias=True))
model.add(BatchNormalization())

model.add(Conv3D(filters=1, kernel_size=(3, 3, 3), padding='same', data_format='channels_last'))


MODEL_DIR = os.getcwd()
version = 1
export_path = os.path.join(MODEL_DIR, str(version))
print('export_path= {}\n'.format(export_path))

keras.models.save_model(
    model,
    export_path,
    save_format='tf'
)

print('\nSaved model:')