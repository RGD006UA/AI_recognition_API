import requests
from pprint import pprint
import json
import random
from hashlib import sha256

url_create_encoding = "https://api.passport.evergreens.com.ua/dbapi/create_encoding/"
url_store_encoding = "https://api.passport.evergreens.com.ua/dbapi/store_encoding/"
url_search_encoding = "https://api.passport.evergreens.com.ua/dbapi/sync_search_encoding/"

sign = None
timestamp = None

def create_encoding(path_of_json_encoding: str):
    global sign, timestamp
    with open(path_of_json_encoding, 'rb') as json_create_encoding:
        json_with_base64 = json.load(json_create_encoding)
        
        sign = sha256(str(json_with_base64['timestamp'] + 
                             json_with_base64["sign"] + 
                             json_with_base64["timestamp"]).encode("utf-8")).hexdigest()
        timestamp = json_with_base64['timestamp']
    
        multipart_form_data = (
                ("file_1", (json_with_base64["file_1"], open(json_with_base64["file_1"], 'rb'))),
                ("sign", (None, sign)),
                ("timestamp", (None, json_with_base64["timestamp"]))
        )
        # print(multipart_form_data)
        response = requests.post(url_create_encoding, files=multipart_form_data)
        # pprint(response.json())
        return response.json()["encoding"]
        

encoding_left = create_encoding("../json_requests/create_encoding_left.json")
encoding_right = create_encoding("../json_requests/create_encoding_right.json")


encoding = {
            "collection_id": "sukhomlin.vladyslav@lll.kpi.ua",
            "encoding": encoding_left,
            "encodings_data": [
                {
                "base64": "string",
                "data": "string"
                }
            ],
            "guid": "sukhomlin.vladyslav@lll.kpi.ua_" + str(random.randint(100000, 999999)),
            'body': "string",
            "callback_url": "string",
            'inn': "string",
            "sign": sign,
            "timestamp": timestamp
            }

# print(sign, timestamp)

response = requests.post(url_store_encoding, json=encoding)
# pprint(response.json())
response_after_saving = response.json()

json_search_encoding = {
  "collection_id": "sukhomlin.vladyslav@lll.kpi.ua",
  "encoding": encoding_right,
  "guids": [response_after_saving["guid"]],
  "id": response_after_saving["id"],
  "limit": 1,
  "max_score": 0,
#   "body": "string",
  "callback_url": "string",
  "sign": sign,
  "source_guid": "string",
  "timestamp": timestamp,
}

response = requests.post(url_search_encoding, json=json_search_encoding)
# pprint(response.json())

with open("../json_requests/result.json", "w") as result_json:
    json.dump(response.json()["encodings"][0], result_json, indent=4)

print("succes")