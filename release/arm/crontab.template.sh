#!/bin/bash
URL='http://127.0.0.1:80/json.rpc' 

curl -v -X POST --retry 5 --retry-delay 1 -d '{"jsonrpc": "2.0", "method": "pca9685Set", "params": {"channel": 0, "dutty": 100}, "id": 100}'  $URL
sleep 1
curl -v -X POST --retry 5 --retry-delay 1 -d '{"jsonrpc": "2.0", "method": "pca9685Set", "params": {"channel": 1, "dutty": 75}, "id": 101}'  $URL
sleep 1
curl -v -X POST --retry 5 --retry-delay 1 -d '{"jsonrpc": "2.0", "method": "pca9685Set", "params": {"channel": 2, "dutty": 50}, "id": 102}'  $URL

