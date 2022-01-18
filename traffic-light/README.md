# traffic-light

This project is run on a ATTINY85 in a 3d-printed traffic light that has a single pushbutton for user inputs.

It operates in three modes:

- automatic mode
- yellow flash mode
- manual mode

### Automatic mode

Traffic light transitions between phases automatically with a fixed timing configuration for each phase.

### Yellow flash mode

Traffic light flashes the yellow light in a periodic interval, e.g. on less frequented crossings in real life at night time.

### Manual mode

Button inputs trigger state transitions explicitly.

## User inputs

Users can select a mode at any time by pressing the button for a specific amount of time:

Press button for:

- <2s to trigger a manual state transition or enter manual mode
- \>2s and <4s to enter automatic mode
- \>5s to enter yellow flashing mode
