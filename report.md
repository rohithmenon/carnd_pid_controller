# PID controller for Auto Steer

Objective of the project is to auto steer a car in simulation so as to keep cross-track error close to 0 and driving as fast as possible.

1. [Problem setup](#problem_setup)
2. [PID controller](#controller)
3. [Tuning](#tuning)
4. [Reflection](#reflection)

## <a name="problem_setup">Problem setup</a>
Simulator executes in autonomous mode streaming cross track error on web-socket. Simulator accepts steering angle and throttle on a web-socket. A PID controller is to be designed to keep cross-track error close to 0 while driving the car as fast as possible.

## <a name="controller">Controller</a>
To achieve the objective, two controllers are used. One controller to compute steering angle and another to compute throttle.

### AutoSteer controller
PID controller to compute steer angle. We start with a P only controller. Proportional only conroller is able to maintain the car within the drivable area but at very low speeds. Kp = 0.2 achieves the goal of the project, but breaks at speed of 30. Also there is oscillation with just proportional controller. To solve this a derivative control was added. PD controller works pretty well but it fails to capture constant turn rate for curves. To address this an integral gain is added. This ensures that any contant steering angle that must be maintained is calculated by the controller. The car drives well at throttle of 50. To drive at higher speeds, we need another controller because the car needs to slow down at turns. This is the throttle controller.

### Throttle controller
Throttle controller is pretty simple. It does not have a derivative component. It is just an I controller which increases throttle when abs(CTE) < 0.6 and decreases otherwise. The parameters are setup such that the car slows down 1.5 times faster than speed up. This ensures that car can slow down quickly around the turns.

## <a name="tuning">Tuning</a>
Parameters of the controller were tuned manually by following the Twiddle algorithm. The simulator does not provide a way to automate the hyper parameter search and hence I manually adjusted the parameters while checking CTE. First a viable P gain was selected by Twiddling, then a D gain was selected to reduce the oscillation. After introducing D, trying higher values of P did not offer better performance. Once reasonable values for PD controller was found, a good value for I was searched again using Twiddle. Only addition to I controller was a decay for the accumulated errors.

### AutoSteer params
Kp = 0.1<br>
Ki = 0.00055<br>
Kd = 3.0<br>
decay = 0.99

### Throttle controller params
Ki = 0.002<br>
decay = 0.999

## <a name="results">Results</a>
Here is a [video](./pid_autosteer.mov) of the controller in action.

## <a name="reflection">Reflection</a>
This was super easy to code and was fun to see it in action. Tuning was done manually although Twiddle was followed. It would have been much easier to perform automated parameter sweeps if the track in the simulator could have been started and stopped programmatically. I have been recently reading upon Gaussian processes and such hyper parameter search can be more efficiently done by Bayesian optimization especially given the small parameter space.
