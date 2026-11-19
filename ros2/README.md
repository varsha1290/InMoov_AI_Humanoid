# ROS 2 integration — pending measured robot geometry

Final ROS 2 description and simulation packages are not generated because the actual STL files, joint axes, origins, limits, masses and inertias are not yet available.

Next steps:
1. Add licensed STL/mesh files under an inmoov_description/meshes directory.
2. Measure each joint origin and axis from the actual assembly.
3. Define URDF/Xacro links and joints.
4. Add realistic inertial and collision geometry.
5. Add a ros2_control hardware interface or serial bridge to the ESP32 protocol.
6. Validate in RViz before simulation.
