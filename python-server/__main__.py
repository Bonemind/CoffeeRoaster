from database import database as db
from web import server as server
# from roasting.roastingmanager import RoastingManager

if __name__ == "__main__":
    server.run_server()
    # if False:
    #     profile = db.Profile.get(db.Profile.name == "Bland")
    #     stageQuery = db.Stage.select().where(db.Stage.profile == profile).order_by(db.Stage.sequence_number.asc())
    #     stages = []
    #     for stage in stageQuery:
    #         print stage
    #         stages.append(stage)

    #     print stages

    #     roastingmanager = RoastingManager(stages)
    #     roastingmanager.setInterval(1)
    #     roastingmanager.start()
    #     print "ran roastingmanager"
