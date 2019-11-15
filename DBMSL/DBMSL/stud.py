from pymongo import MongoClient

client = MongoClient('10.10.11.42',27017)

db = client.te3177db

stud = db.student

rec = { "name": "John", "address": "Highway 37" }

x = stud.insert_one(rec)

print(x.inserted_id)

x = { "name":"John" }

stud.delete_one(x)
