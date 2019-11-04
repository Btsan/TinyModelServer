#!/bin/bash
set -e

echo "Serializing models..."
cd models && python serialize_models.py


echo "deb [arch=amd64] http://storage.googleapis.com/tensorflow-serving-apt stable tensorflow-model-server tensorflow-model-server-universal" | sudo tee /etc/apt/sources.list.d/tensorflow-serving.list && \
curl https://storage.googleapis.com/tensorflow-serving-apt/tensorflow-serving.release.pub.gpg | sudo apt-key add -
apt-get update && apt-get install tensorflow-model-server
apt-get upgrade tensorflow-model-server

cd .. && echo "Starting server..."
nohup tensorflow_model_server \
  --rest_api_port=8501 \
  --model_config_file=models.config >server.log 2>&1