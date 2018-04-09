int** portSettings = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
class Controller{private:
  int ID;
  SlidePot X;
  SlidePot Y;
  int aBut;
  int bBut;
  int jBut;
  public:
    Controller();
    ~Controller();
    double getJAngle();
    double getJX();
    double getJY();
    bool getA();
    bool getB();
    bool getJ();
}


class SlidePot{ private:
  uint32_t data;     // raw ADC value
  int32_t flag;      // 0 if data is not valid, 1 if valid
  uint32_t distance; // distance in 0.001cm
// distance = (slope*data+offset)/4096
  uint32_t slope;    // calibration coeffients
  uint32_t offset;
public:
  SlidePot(uint32_t m, uint32_t b); // initialize slide pot
  void Save(uint32_t n);        // save ADC, set semaphore
  void Sync(void);              // wait for semaphore
  uint32_t Convert(uint32_t n); // convert ADC to raw sample
  uint32_t ADCsample(void);     // return last ADC sample value (0 to 4095)
  uint32_t Distance(void);      // return last distance value (0 to 2000), 0.001cm
};