from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class BoxDrop(LineReceiver):

   def lineReceived(self, line):
      print line

class BoxDropFactory(Factory):

   def __init__(self):
      pass

   def buildProtocol(self, address):
      return BoxDrop()

reactor.listenTCP(60000, BoxDropFactory())
reactor.run()
   
