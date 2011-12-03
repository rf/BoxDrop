from twisted.internet import inotify
from twisted.python import filepath
from twisted.internet import reactor

class NotifyHandler(object):

    def __init__(self):
        pass

    def notify(self, ignored, path, mask):
        print 'event {} on {}'.format(
            inotify.humanReadableMask(mask),
            path
        )

handler = NotifyHandler()
notifier = inotify.INotify()
notifier.startReading()
notifier.watch(filepath.FilePath("/tmp"), callbacks=[handler.notify])

reactor.run()
