#!/bin/bash
set -e

python modelmake

echo "deb [arch=amd64] http://storage.googleapis.com/tensorflow-serving-apt stable tensorflow-model-server tensorflow-model-server-universal" | sudo tee /etc/apt/sources.list.d/tensorflow-serving.list && \
curl https://storage.googleapis.com/tensorflow-serving-apt/tensorflow-serving.release.pub.gpg | sudo apt-key add -
apt-get update && apt-get install tensorflow-model-server
apt-get upgrade tensorflow-model-server

nohup tensorflow_model_server \
	--rest_api_port=8501 \
	--model_name=TinyModel \
	--model_base_path=$(pwd)/model/

cd ../example

git clone https://github.com/curl/curl.git

make