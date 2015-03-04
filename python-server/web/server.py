from database import database as db
from flask import Flask
from flask_peewee.db import Database
from flask_peewee.auth import Auth
from flask_peewee.admin import Admin
from flask_peewee.rest import RestAPI, UserAuthentication
from flask_peewee.serializer import Serializer

#flask-peewee config
DATABASE = {
        "name": "roaster.db",
        "engine": "peewee.SqliteDatabase"
}
SECRET_KEY = "HUSHH"
DEBUG = True

#app init
app = Flask(__name__)
app.config.from_object(__name__)

#flask peewee init
flask_peewee_db = Database(app)
flask_peewee_auth = Auth(app, flask_peewee_db)
flask_peewee_admin = Admin(app, flask_peewee_auth)

#flask-peewee admin init
flask_peewee_admin.register(db.Coffee)
flask_peewee_admin.register(db.Stage)
flask_peewee_admin.register(db.StageType)
flask_peewee_admin.register(db.Profile)
flask_peewee_auth.register_admin(flask_peewee_admin)
flask_peewee_admin.setup()

#flask-peewee api init
user_auth = UserAuthentication(flask_peewee_auth)
api = RestAPI(app, default_auth=user_auth)
api.register(db.Coffee)
api.register(db.Stage)
api.register(db.StageType)
api.register(db.Profile)
api.setup()

@app.route("/api/coffee/<id>/profiles")
def testroute(id):
    coffee = db.Coffee.get(db.Coffee.id == id)
    profiles = db.Profile.select().where(db.Profile.coffee == coffee)
    for profile in profiles:
        print profile
    serializer = Serializer()
    print serializer.serialize_object(profiles)
    return id

def InitializeDatabase():
    try:
        os.remove("roaster.db")
    except:
        pass;
    flask_peewee_auth.User.create_table(fail_silently = False)
    admin = flask_peewee_auth.User(username = "admin", email='', admin=True, active=True)
    admin.set_password("admin")
    admin.save()

def run_server():
        app.run()
