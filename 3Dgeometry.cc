#define REP(i,s,n) for(int i=s;i<n;i++)
#define rep(i,n) REP(i,0,n)
#define EPS (1e-7)
#define equals(a,b) (fabs((a)-(b))<EPS)
 
using namespace std;
 
//作成中 VerifyしたものにはVerifyと書いてある
 
//Verify AOJ 0115
class Point3d{
public:
  double x,y,z;
 
  Point3d(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
 
  Point3d operator + (const Point3d& a){
    return Point3d(x+a.x,y+a.y,z+a.z);
  }
  Point3d operator - (const Point3d& a){
    return Point3d(x-a.x,y-a.y,z-a.z);
  }
  Point3d operator * (const double& d){
    return Point3d(x*d,y*d,z*d);
  }
  Point3d operator / (const double& d){
    return Point3d(x/d,y/d,z/d);
  }
 
  bool operator < (const Point3d& p)const { return !equals(x,p.x)?x<p.x:((!equals(y,p.y))?y<p.y:(!equals(z,p.z)&&z<p.z)); }
 
  bool operator == (const Point3d& p)const{
    return equals(x,p.x) && equals(y,p.y) && equals(z,p.z);
  }
 
};
 
//Verify AOJ 0115
struct Segment3d{
  Point3d p[2];
  Segment3d(Point3d p1=Point3d(),Point3d p2=Point3d()){
    p[0] = p1, p[1] = p2;
  }
 bool operator == (const Segment3d& seg)const{
    return ( p[0] == seg.p[0] && p[1] == seg.p[1] ) || ( p[0] == seg.p[1] && p[1] == seg.p[0] );
 }
};
 
typedef Point3d Vector3d;
typedef Segment3d Line3d;
  
ostream& operator << (ostream& os,const Point3d& p){
  os << "(" << p.x << "," << p.y << "," << p.z << ")";
}
 
ostream& operator << (ostream& os,const Segment3d& seg){
  os << "(" << seg.p[0] << "," << seg.p[1] << ")";
}
 
//Verify AOJ 0115
double dot(const Point3d& a,const Point3d& b){
  return a.x*b.x + a.y*b.y + a.z*b.z;
}
 
//Verify AOJ 0115
Vector3d cross(const Point3d& a,const Point3d& b){
  return Vector3d(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
 
//Verify AOJ 0115
inline double norm(const Point3d &p){
  return p.x*p.x + p.y*p.y + p.z*p.z;
}
 
//Verify AOJ 0115
inline double abs(const Point3d &p){
  return sqrt(norm(p));
}
 
inline double toRad(double theta){
  return theta * M_PI / 180.0;
}
 
 
 // Verify AOJ 1331
bool on_line3d(Line3d line,Point3d p){
  return equals(abs(cross(p-line.p[0],line.p[1]-line.p[0])),0);
}
 
// Verify AOJ 1331
bool on_segment3d(Segment3d seg,Point3d p){
  if( !on_line3d(seg,p) ) return false;
  double dist[3] = { abs(seg.p[1]-seg.p[0]), abs(p-seg.p[0]), abs(p-seg.p[1]) };  
  return on_line3d(seg,p) && equals(dist[0],dist[1]+dist[2]);
}
 
//Verify AOJ 0115
bool point_on_the_triangle3d(Point3d tri1,Point3d tri2,Point3d tri3,Point3d p){
 
  //線分上にpがあった場合、三角形内とみなす
  //if( on_segment3d(Segment3d(tri1,tri2),p) ) return true;
  //if( on_segment3d(Segment3d(tri2,tri3),p) ) return true;
  //if( on_segment3d(Segment3d(tri3,tri1),p) ) return true;

  vector<Point3d> vec(3);
  vec[0] = tri1, vec[1] = tri2, vec[2] = tri3;
  double area = 0;
  {
    double a = abs(vec[0]-vec[1]), b = abs(vec[1]-vec[2]), c = abs(vec[2]-vec[0]);
    double s = ( a + b + c ) / 2;
    area = sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
  }
  double sum = 0;
  rep(i,3){
    double a = abs(vec[i]-vec[(i+1)%3]), b = abs(vec[(i+1)%3]-p), c = abs(p-vec[i]);
    double s = ( a + b + c ) / 2;
    sum += sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
  }
  return equals(sum,area);

// ---------- 以下はバグ有りと思われる ---------

  Vector3d v1 = tri2 - tri1;
  Vector3d v2 = tri3 - tri2;
  Vector3d v3 = tri1 - tri3;
 
  Vector3d cp[3] = { cross(v1,p-tri1), cross(v2,p-tri2), cross(v3,p-tri3) };
  double d1 = dot(cp[0],cp[1]);
  double d2 = dot(cp[0],cp[2]);
 
  // 線分上にpがあった場合,三角形内とはみなさない
  //if( ( !equals(d1,0.0) && d1 > 0 ) && ( !equals(d2,0.0) && d2 > 0 ) ) return true;
 
  // 線分上にpがあった場合,三角形内とみなす
  if( ( equals(d1,0.0) || d1 > 0 ) && ( equals(d2,0.0) || d2 > 0 ) ) return true;
  return false;
}
 
inline Point3d rotateX(Point3d p,double rad){
  return Point3d(p.x,p.y*cos(rad)-p.z*sin(rad),p.y*sin(rad)+p.z*cos(rad));
}
 
inline Point3d rotateY(Point3d p,double rad){
  return Point3d(p.x*cos(rad)+p.z*sin(rad),p.y,-p.x*sin(rad)+p.z*cos(rad));
}
 
inline Point3d rotateZ(Point3d p,double rad){
  return Point3d(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad),p.z);
}
 
inline Point3d rotateEuler(Point3d p,double alpha,double beta,double gamma){
  return Point3d( (cos(alpha)*cos(beta)*cos(gamma)-sin(alpha)*sin(gamma)) * p.x + (-cos(alpha)*cos(beta)*sin(gamma)-sin(alpha)*cos(gamma)) * p.y + (cos(alpha)*sin(beta)) * p.z,
		  (sin(alpha)*cos(beta)*cos(gamma)+cos(alpha)*sin(gamma)) * p.x + (-sin(alpha)*cos(beta)*sin(gamma)+cos(alpha)*cos(gamma)) * p.y + (sin(alpha)*sin(beta)) * p.z,
		  (-sin(beta)*cos(gamma)) * p.x + (sin(beta)*sin(gamma)) * p.y + (cos(beta)) * p.z);
}
 
inline Point3d rotateRollPitchYaw(Point3d p,double roll,double pitch,double yaw){
  return Point3d( ( cos(roll) * cos(pitch) ) * p.x + ( cos(roll) * sin(pitch) * sin(yaw) - sin(roll) * cos(yaw) ) * p.y + ( cos(roll) * sin(pitch) * cos(yaw) + sin(roll) * sin(yaw) ) * p.z,
		  ( sin(roll) * cos(pitch) ) * p.x + ( sin(roll) * sin(pitch) * sin(yaw) + cos(roll) * cos(yaw) ) * p.y + ( sin(roll) * sin(pitch) * cos(yaw) - cos(roll) * sin(yaw) ) * p.z,
		  -sin(pitch) * p.x + cos(pitch) * sin(yaw) * p.y + cos(pitch) * cos(yaw) * p.z);
}
 
 
class Plane3d{
public:
  Point3d normal_vector; //法線ベクトル
  double d; // 平面方程式 normal_vector.x * x + normal_vector.y * y + normal_vector.z * z + d = 0
 
  Plane3d(Point3d normal_vector=Point3d(),double d=0):normal_vector(normal_vector),d(d){}
  Plane3d(Vector3d a,Vector3d b,Vector3d c){
    Vector3d v1 = b - a;
    Vector3d v2 = c - a;
    Vector3d tmp = cross(v1,v2);
    normal_vector = tmp / abs(tmp);
    set_d(a);
  }
 
  //Verify AOJ 0115
  //法線ベクトルnormal_vectorと平面上の１点からdを計算する
  void set_d(Point3d p){
    d = dot(normal_vector,p);
  }
 
// Verify Yukicoder No132
  //平面と点pの距離を求める
  double distanceP(Point3d p){
    Point3d a = normal_vector * d;//平面上の適当な点をつくる
    return abs( dot(p-a,normal_vector) );
  }
 
  //平面上でもっとも点pと近い点を求める
  Point3d nearest_point(Point3d p){
    Point3d a = normal_vector * d;
    return p - ( normal_vector * dot(p-a,normal_vector) );
  }
 
  //Verify AOJ 0115
  //平面と線分が交差するか
  bool intersectS(Segment3d seg){
    Point3d a = normal_vector * d;
    double res1 = dot(a-seg.p[0],normal_vector);
    double res2 = dot(a-seg.p[1],normal_vector);
    if( res1 > res2 ) swap(res1,res2);
    //cout << res1 << " < " << res2 << endl;
    if( ( equals(res1,0.0) || res1 < 0 ) && ( equals(res2,0.0) || res2 > 0 ) ) return true;
    return false;
  }
 
  //Verify AOJ 0115
  //平面と線分の交点を求める
  Point3d crosspointS(Segment3d seg){
    Point3d a = normal_vector * d;
    double dot_p0a = fabs(dot( seg.p[0]-a,normal_vector ));
    double dot_p1a = fabs(dot( seg.p[1]-a,normal_vector ));
    if( equals(dot_p0a+dot_p1a,0) ) return seg.p[0];
    return seg.p[0] + ( seg.p[1] - seg.p[0] ) * ( dot_p0a / ( dot_p0a + dot_p1a ) );
  }
 
};
 
double distanceLP(Line3d line,Point3d p){
  return abs(cross(line.p[1]-line.p[0],p-line.p[0])) / abs(line.p[1]-line.p[0]);
}
 
// Verify AOJ 1331
Point3d project(Segment3d seg,Point3d p){
  Vector3d base = seg.p[1] - seg.p[0];
  double t = dot(p-seg.p[0],base) / norm(base);
  return seg.p[0] + base * t;
}
 
// Verify AOJ 1331
Point3d reflect(Segment3d seg,Point3d p){
  return p + (project(seg,p)-p) * 2.0;
}

// Verify AOJ 1331
double distanceSP(Segment3d seg,Point3d p){
  Point3d r = project(seg,p);
  if( on_segment3d(seg,r) ) return abs(p-r);
  return min(abs(seg.p[0]-p),abs(seg.p[1]-p));
}

//Verify AOJ 2081
bool isParallel(Line3d l1,Line3d l2){
  Vector3d A = l1.p[0], B = l1.p[1], C = l2.p[0], D = l2.p[1];
  Vector3d AB = B - A, CD = D - C;
  Vector3d n1 = AB / abs(AB), n2 = CD / abs(CD);
  double tmp = dot(n1,n2);
  tmp = 1 - tmp*tmp;
  return equals(tmp,0.0);
}
 
//Verify AOJ 2081 
//l1,l2が平行な時には使用できないので注意
Segment3d nearest_segmentLL(Line3d l1,Line3d l2){
  assert(!isParallel(l1,l2)); // 平行な場合は使用不可
  // l1.p[0] = A, l1.p[1] = B, l2.p[0] = C, l2.p[1] = D
  Vector3d AB = l1.p[1] - l1.p[0];
  Vector3d CD = l2.p[1] - l2.p[0];
  Vector3d AC = l2.p[0] - l1.p[0];
  Vector3d n1 = AB / abs(AB), n2 = CD / abs(CD);
  double d1 = (dot(n1,AC)-dot(n1,n2)*dot(n2,AC)) / (1.0-pow(dot(n1,n2),2));
  double d2 = (dot(n1,n2)*dot(n1,AC)-dot(n2,AC)) / (1.0-pow(dot(n1,n2),2));
  return Segment3d(l1.p[0]+n1*d1,l2.p[0]+n2*d2);
}
 
//Verify AOJ 2081
bool intersectLL(Line3d l1,Line3d l2){
  Vector3d A = l1.p[0], B = l1.p[1], C = l2.p[0], D = l2.p[1];
 
  //そもそもl1,l2が直線じゃない
  if( equals(abs(B-A),0.0) || equals(abs(D-C),0.0) ){
    /*
      この場合は注意
      そもそも与えられた線分が線分になっていないので、交差するかどうかは判定できない
    */
    return false;
  }
 
  Vector3d AB = B - A, CD = D - C;
  Vector3d n1 = AB / abs(AB), n2 = CD / abs(CD);
  double tmp = dot(n1,n2);
  tmp = 1 - tmp*tmp;
 
  if( equals(tmp,0.0) ) return 0; // 直線が平行
 
  Segment3d ns = nearest_segmentLL(l1,l2);
  if( ns.p[0] == ns.p[1] ) return true;
  return false;
}

bool intersectSS(Segment3d seg1,Segment3d seg2){
  if( isParallel(seg1,seg2) ) return false;
  Segment3d seg = nearest_segmentLL(seg1,seg2);
  if( !( seg.p[0] == seg.p[1] ) ) return false;
  Point3d cp = seg.p[1];
  return on_segment3d(seg1,cp) && on_segment3d(seg2,cp);
}

typedef pair<Point3d,bool> P3db;

/* 
一応AOJ2562でVerifyしたが不安なので別の問題でもテストしてみること
Input:
２つの平面pl1,pl2
Output:
２つの平面が交線をもつ場合     -> first:交線上の任意の１点, second:true
　　　　　　交線を持たない場合 -> first:empty            , second:false

 */
P3db intersectPlPl(const Plane3d &pl1,const Plane3d &pl2){
  Vector3d v = cross(pl1.normal_vector,pl2.normal_vector);
  if( !equals(v.x,0.0) ){
    return P3db(Point3d(0,
                        (pl1.d*pl2.normal_vector.z-pl2.d*pl1.normal_vector.z)/v.x,
                        (pl1.d*pl2.normal_vector.y-pl2.d*pl1.normal_vector.y)/(-v.x)),true);
  }
  if( !equals(v.y,0.0) ){
    return P3db(Point3d((pl1.d*pl2.normal_vector.z-pl2.d*pl1.normal_vector.z)/(-v.y),
                         0,
                        (pl1.d*pl2.normal_vector.x-pl2.d*pl1.normal_vector.x)/v.y),true);
  }
  if( !equals(v.z,0.0) ){
    return P3db(Point3d((pl1.d*pl2.normal_vector.y-pl2.d*pl1.normal_vector.y)/v.z,
                        (pl1.d*pl2.normal_vector.x-pl2.d*pl1.normal_vector.x)/(-v.z),
                        0),true);
  }
  return P3db(Point3d(),false);//平行なのでそのような交線は存在しない
}

/* Verify AOJ 2562
Input:
２つの平面plane,plane2とその交線上の任意の１点
Output:
２つの平面の交線

説明:
2つの平面の外積から交線の方向ベクトルを得る
あとは任意の１点に拡張した方向ベクトルを加えてセグメント化する
交線上の任意の１点はintersectPlPlで取得できる
若干面倒な仕様になってしまった
 */
Line3d intersectPlPl_converter(Plane3d plane,Plane3d plane2,Point3d tmp){
  Vector3d ve = cross(plane.normal_vector,plane2.normal_vector);
  return Line3d(tmp,tmp+(ve*10)); // 任意の倍数で拡張、ここでは10
}

// x >= y
bool GTE(double x, double y){ return equals(x,y) || x > y; }

// x > y
bool GT(double x, double y){ return !equals(x,y) && x > y; }

// x < y
bool LT(double x, double y){ return !equals(x,y) && x < y; }

// x <= y
bool LTE(double x, double y){ return equals(x,y) || x < y; }
