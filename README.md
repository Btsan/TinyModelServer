TensorFlow Server with C++ example:

Either run setup.sh or follow these instructions if the script does not work for you

1. install tensorflow serving (https://www.tensorflow.org/tfx/serving/setup)
2. run server (with args: rest_api_port=8501, model_name=TinyModel, model_base_path=$(pwd)/model/)
3. make and run the example