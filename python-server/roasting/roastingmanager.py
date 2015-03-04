from threading import Timer
import time
from taskthread import TaskThread
import serial

class RoastingManager(TaskThread):
	starttime = -1 
	stages = None
	currentStage = None
	done = False
	serial_port = serial.Serial("COM4", 9600)

	def __init__(self, stages):
		TaskThread.__init__(self)
		self.stages = stages

	def start(self):
		TaskThread.start(self)
		data = ""
		while data != "Ready":
			data += self.serial_port.read()
		self.next_stage()

	def next_stage(self):
		#there is no next stage, flag the roast as done and return
		if len(self.stages) == 0:
			self.done = True
			return

		self.currentStage = self.stages.pop(0)
		if self.currentStage.stage_type.id_number > 2:
			raise Exception("Stage number is higher than it should be")

		self.starttime = -1

		self.set_stage()
		#if this is a cooling stage, start timing
		if self.currentStage.stage_type.name == "Cooling":
			self.starttime = time.time()

	def set_stage(self):
		self.serial_port.write("setstage {0} {1}\n".format(self.currentStage.stage_type.id_number, self.currentStage.target_temperature))
		self.serial_port.flush()

	def task(self):
		if self.done:
			self.serial_port.write("setstage {0}\n".format(0))
			self.serial_port.flush()
			self.serial_port.close()
			self._finished.set()

		if not self.currentStage:
			return

		if self.currentStage.stage_type.name == "Heating":
			#check if the beans have the correct temp (i.e we've recieved t-ok)
			data = ""
			while self.serial_port.inWaiting() > 0:
				print "SerialWaiting";
				data += self.serial_port.read(self.serial_port.inWaiting())
				print data
				if "t-ok" in data and self.starttime == -1:
					self.starttime = time.time()


		#starttime == -1, placeholder for we don't want to time this stage yet, return
		if self.starttime == -1:
			return


		if self.starttime + self.currentStage.duration < time.time():
			self.next_stage()

	#write to arduino


