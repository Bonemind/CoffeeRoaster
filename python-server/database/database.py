from peewee import *

db = SqliteDatabase("roaster.db")

class BaseModel(Model):
    """
    The basic model all our models will inherit from
    """
    class Meta:
    	database = db

class Coffee(BaseModel):
    """
    Contains the coffee's we'll be roasting
    """
    name = CharField()

    def __unicode__(self):
        return self.name

class Profile(BaseModel):
    """
    Contains roasting profiles for a coffee
    """
    name = CharField()
    coffee = ForeignKeyField(Coffee)
    def __unicode__(self):
        return self.name

class StageType(BaseModel):
    """
    Contains the stages we can define in a profile
    """
    name = CharField(unique = True)
    id_number = IntegerField(unique = True)
    def __unicode__(self):
        return self.name

class Stage(BaseModel):
    """
    The stages a profile is built out of
    """
    stage_type = ForeignKeyField(StageType)
    target_temperature = DoubleField()
    duration = IntegerField()
    profile = ForeignKeyField(Profile)
    sequence_number = IntegerField()

    def __unicode__(self):
        return self.stage_type.name


def InitializeDatabase():
    db.connect()
    db.create_tables([ Coffee, Profile, StageType, Stage ], True)
    idleStage = StageType(name = "Idle", id_number = 0)
    idleStage.save()
    heatingStage = StageType(name = "Heating", id_number = 1)
    heatingStage.save()
    coolingStage = StageType(name = "Cooling", id_number = 2)
    coolingStage.save()

def CreateTestData():
#stage loading
    idleStage = StageType.get(StageType.name == "Idle")
    heatingStage = StageType.get(StageType.name == "Heating")
    coolingStage = StageType.get(StageType.name == "Cooling")
#Coffee
    peru_tunki = Coffee(name = "Peru Tunki")
    lampekoy = Coffee(name = "Lampekoy")
    peru_tunki.save()
    lampekoy.save()
#Profiles
    bland = Profile(name = "Bland", coffee = peru_tunki)
    lampekoy_bland = Profile(name = "Bland", coffee = lampekoy)
    bland.save()
    lampekoy_bland.save()

#Stages
    tunki_heating_1 = Stage(stage_type = heatingStage, target_temperature = 195, duration = 0, profile = bland, sequence_number = 0)
    tunki_heating_2 = Stage(stage_type =  heatingStage, target_temperature = 200, duration = 30, profile = bland, sequence_number = 1)
    tunki_heating_3 = Stage(stage_type = heatingStage, target_temperature = 205, duration = 0, profile = bland, sequence_number = 2)
    tunki_heating_1.save()
    tunki_heating_2.save()
    tunki_heating_3.save()
    tunki_cooling = Stage(stage_type = coolingStage, target_temperature = 0, duration = 300, profile = bland, sequence_number = 3);
    tunki_cooling.save()


    
