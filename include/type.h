struct Imu_data
{
    double a_[3];
    double w_[3];

    Imu_data(double a[3],double w[3]): a_{a[0],a[1],a[2]},w_{w[0],w[1],w[2]};
    Imu_data(double ax,double ay,double az, double wx, double wy, double wz):a_{ax,ay,az},w_{wz,wy,wz};
};


// struct Imu_odom_pose_data
// {
//     Imu_data imu_data_;
//     double pose_[3];
//     double quat_[4];
//     double timestamp_;
//     double vx_,vy_;
//     double angle_v_;

//     imu_odom_pose_data(double pose[3],double quat[4],double vx, double vy, double angle_v, Imu_data imu_data, double t): pose_(a),quat_(w),vx_(vx),vy_(vy),angle_v_(angle_v),imu_data_(Imu_data),timestamp_(t);
//     imu_odom_pose_data(double x,double y,double z, double qw, double qx, double qy, double qz,double t,double vx, double vy, double angle_v, Imu_data imu_data , double t):pose_({x,y,z}),quat_({qw,qx,qy,qz}),timestamp_(t),vx_(vx),vy_(vy),angle_v_(angle_v),imu_data_(Imu_data);
// };

struct Odom_data
{
    // Imu_data imu_data_;
    double pose_[3];
    double quat_[4];
    double timestamp_;
    double vx_,vy_;
    double angle_v_;

    Odom_data(double pose[3],double quat[4],double t,double vx, double vy, double angle_v): pose_(pose),quat_(quat),timestamp_(t),vx_(vx),vy_(vy),angle_v_(angle_v);
    Odom_data(double x,double y,double z, double qw, double qx, double qy, double qz, double t,double vx, double vy, double angle_v):pose_({x,y,z}),quat_({qw,qx,qy,qz}),timestamp_(t),vx_(vx),vy_(vy),angle_v_(angle_v);
};
struct Imu_odom_pose_data
{
    Imu_data imu_data_;
    Odom_data odom_data;
    Imu_odom_pose_data(Imu_data,Odom_data):imu_data_(Imu_data),
};
