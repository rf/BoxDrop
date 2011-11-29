from twisted.internet.protocol import ClientFactory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor
import json

class BoxDrop(LineReceiver):

   def connectionMade(self):
      self.sendLine('{"test":"hello"}')

   def lineReceived(self, line):
      print json.loads(line)

class BoxDropClientFactory(ClientFactory):
   
   def buildProtocol(self, addr):
      print 'connected'
      return BoxDrop()

reactor.connectTCP('localhost', 60000, BoxDropClientFactory())
reactor.run()
