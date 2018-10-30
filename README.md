
# vw_generator

Transform encoder data from left right representation to velocity and angular velocity representation.

## Publish
* topic vw_estimate, std_msgs/Float32MultiArray (velocity and angular velocity)

Velocity is placed at position "0" and angular velocity at "1".

## Subscribe
* topic wheel_velocity, std_msgs/Float32MultiArray (left and right velocity)

Array index "0" is for left wheel.
Array index "1" is for right wheel.
