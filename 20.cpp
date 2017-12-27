#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>


class Velocity {
public:
  long long x, y, z;
  Velocity(long long x, long long y, long long z): x(x), y(y), z(z) {}

  Velocity operator *(const long long& t) {
    return Velocity(t*x,t*y,t*z);
  }

  Velocity operator +(const Velocity& t) {
    return Velocity(t.x+x,t.y+y,t.z+z);
  }
};
class Acceleration {
public:
  long long x, y, z;
  Acceleration(long long x, long long y, long long z): x(x), y(y), z(z) {}

  double normalized() {
    return sqrt(x*x+y*y+z*z);
  }

  Velocity operator*(const long long& t) {
    return Velocity(t*x,t*y,t*z);
  }

};



class Position {
public:
  long long x, y, z;
  Position(long long x, long long y, long long z): x(x), y(y), z(z) {}

  Position operator+(const Velocity& v) {
    return Position(x+v.x,y+v.y,z+v.z);
  }

  bool operator==(const Position& p) {
    return x==p.x && y == p.y && z == p.z;
  }

};

std::ostream &operator<<(std::ostream& o, const Position& p) {
  return o << "Position(" << p.x << ", " << p.y << ", " << p.z << ")";
}

std::ostream &operator<<(std::ostream& o, const Velocity& v) {
  return o << "Velocity(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream &operator<<(std::ostream& o, const Acceleration& a) {
  return o << "Acceleration(" << a.x << ", " << a.y << ", " << a.z << ")";
}


class Particle {
public:
  Position p_;
  Velocity v;
  Acceleration a_;

  Particle(Position p, Velocity v, Acceleration a): p_(p),v(v),a_(a) {}

  Position positionAt(long long t) {
    return p_ + v*t + a_*(t*(t+1)/2);
  }

  friend std::ostream &operator<<(std::ostream& o, const Particle& p);

  void tick() {
    v = v + Velocity(a_.x, a_.y, a_.z);
    p_ = p_ + v;
  }

  bool collide(Particle& p2) {
    std::vector<long long> t;

    double a = a_.x - p2.a_.x;
    double b = v.x - p2.v.x;
    double c = p_.x - p2.p_.x;

    if(a == 0) {
      // (b * t + c)
      if(b == 0) {
        long long solution = 0;
        if(p2.positionAt(solution) == positionAt(solution)) {
          return true;
        }
        return false;
      }
      // bt + c = 0
      long long solution = -c / (double)b;
      if(p2.positionAt(solution) == positionAt(solution)) {
        //std::cout << "Collision for: " << *this << " " << p2 << " At t= " << solution << std::endl;
        return true;
      }
      return false;
    }
    b = b + a/2.;
    a = a/2.;
    for(bool plus : {true, false}) {
      if(plus) {
        long long solution = (-b + (double)(sqrt(b*b-4*a*c))) / (double)(2*a);
        if(p2.positionAt(solution) == positionAt(solution)) {
          //std::cout << "Collision for: " << *this << " " << p2 << " At t= " << solution << std::endl;
          return true;
        }
      } else {
        long long solution = (-b - (double)sqrt(b*b-4*a*c)) / (double)(2*a);
        std::cout << solution << std::endl;
        std::cout << p2.positionAt(solution) << " " << positionAt(solution) << std::endl;
        if(p2.positionAt(solution) == positionAt(solution)) {
          //std::cout << "Collision for: " << *this << " " << p2 << " At t= " << solution << std::endl;
          return true;
        }
      }
    }
    return false;
  }
};


std::ostream &operator<<(std::ostream& o, const Particle& p) {
  return o << "Particle(" << p.p_ << ", " << p.v << ", " << p.a_ << ")";
}




int main() {
  std::ifstream infile("day20input");
  std::string line;
  long long i = 0;
  long long min_i = 0;
  std::vector<Position> positions;
  std::vector<Velocity> velocities;
  std::vector<Acceleration> accelerations;
  std::vector<Particle> particles;

  Particle p1(Position(1582, -423, 3016), Velocity(1, 21, -153), Acceleration(-13, 1, -6));
  Particle p2(Position(-113, 477, 1471), Velocity(42, -79, -10), Acceleration(-4, 6, -11));

  while(std::getline(infile, line)) {
    std::stringstream ss(line);
    char sep;
    long long p[3];
    long long v[3];
    long long a[3];
    ss >> sep >> sep >> sep
       >> p[0] >> sep
       >> p[1] >> sep
       >> p[2] >> sep
       >> sep >> sep >> sep >> sep
       >> v[0] >> sep
       >> v[1] >> sep
       >> v[2] >> sep
       >> sep >> sep >> sep >> sep
       >> a[0] >> sep
       >> a[1] >> sep
       >> a[2] >> sep;
    accelerations.push_back(Acceleration(a[0],a[1],a[2]));
    velocities.push_back(Velocity(v[0],v[1],v[2]));
    positions.push_back(Position(p[0],p[1],p[2]));
    particles.push_back(Particle(positions[i],velocities[i],accelerations[i]));
    if(accelerations[i].normalized() < accelerations[min_i].normalized()) {
      min_i = i;
    }
    i++;
  }
  std::cout << min_i << std::endl;

  std::vector<Particle*> collided(particles.size());

  for(long long i = 0; i < particles.size(); ++i) {
    for(long long j = i+1; j < particles.size(); ++j) {
      if(collided[i] && collided[j]) {
        continue;
      }
      if(particles[i].collide(particles[j])) {
        collided[i] = &particles[j];
        collided[j] = &particles[i];
      }

    }

  }

  long long num_collided = 0;
  i = 0;
  for(bool b : collided) {

    if(!b) {
      //std::cout << particles[i] << std::endl;
      num_collided++;
    }
    i++;
  }
  std::cout << num_collided << std::endl;



}
