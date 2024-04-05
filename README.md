Terminal 1:
```
$ while true; do cat /tmp/ib > /dev/cu.usbmodem14101; sleep 1; done
```
(might need to change the specific modem string)

Terminal 2:
```
$ echo -n "0" >! /tmp/ib
```

Where "0" is a value from:
```
enum Mode {
  SUCCESS = 0,
  FAILURE = 1,
  IN_PROGRESS = 2,
  ENDED = 3,
};
```

