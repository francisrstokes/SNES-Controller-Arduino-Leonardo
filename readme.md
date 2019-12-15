# Super Nintendo / Arduino Leonardo Controller

This project turns a super nintendo controller into a "keyboard" with an arduino leonardo, allowing it to be easily used in an emulator environment.

## Wiring

The Super Nintendo controller plug can be wired to the Arduino in the following way:

```
 ---------------------------------- ---------------------
|                                  |                      \
|  [+5v]    [7]     [5]    [6]     |  [x]    [x]    [Gnd]  |
|                                  |                      /
 ---------------------------------- ---------------------
```

The pins marked with Xs should not be wired to anything, as they are not used.

## Keyboard out

When the sketch is uploaded and the arduino leonardo is running, the controller will output the following keys when the SNES buttons are pressed:

```
    +----------+---------------+
    |   Button | Key           |
    +----------+---------------+
    |     B    |      S        |
    |     Y    |      A        |
    |  Select  |  Right Shift  |
    |   Start  |    Enter      |
    |    Up    |      Up       |
    |   Down   |     Down      |
    |   Left   |     Left      |
    |  Right   |    Right      |
    |     A    |      D        |
    |     X    |      W        |
    |     L    |      E        |
    |     R    |      Q        |
    +----------+---------------+
```

Which can be remapped in the emulator, or changed inside the sketch.

## Further reading

https://gamefaqs.gamespot.com/snes/916396-super-nintendo/faqs/5395

Was a really great resource for understanding how the communication/timing for the controller works.
