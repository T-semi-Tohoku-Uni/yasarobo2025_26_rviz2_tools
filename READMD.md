# yasarobo2025_26_rviz2_tools
これは,`/robot_description`トピックを受け取って，`/home/<username>/install/yasarobo2025_26/share/yasarobo2025_26/...`という文字列を`${HOME}/ros_ws/src/yasarobo2025_26/...`に変換して，`${HOME}/robot_description`トピックをpublishするノードです
実機でテストをする際に，urdfの`.stl`ファイルが実機上での絶対パスで送られてくるので，ローカルで表示させようとするとエラーが出るのでその荒い対処をしたものです．（これがなくても動く．見栄えの問題）

## ubuntu, wsl
```bash
cd ~/ros_ws/src
git clone git@github.com:T-semi-Tohoku-Uni/yasarobo2025_26_rviz2_tools.git
cd ~/ros_ws
colcon build --packages-select yasarobo2025_26_rviz2_tools
source install/setup.bash
```

## macbook用解説
実機のデバッグでrvizが使えないと色々面倒なので，macbookで最低限の可視化ができるようにしてます
### 仮想環境の作成
```bash
pixi init ros_ws -c robostack-staging -c conda-forge
cd ros_ws
pixi add ros-humble-ament-cmake-auto compilers pkg-config cmake ninja
```

### ビルドと実行
```bash
colcon build --cmake-args -G Ninja --packages-select yasarobo2025_26_rviz2_tools
source install/setup.bash
ros2 launch ...
```