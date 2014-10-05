
class Gyro
{
  public:
    Gyro();
    void read();
    int getAngle(int);
  private:
    int offset[3];
    double noise[3];
    L3G gyro;
    double angle[3];
    int rate[3];
};
