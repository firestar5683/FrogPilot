#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8222410327598512542) {
   out_8222410327598512542[0] = delta_x[0] + nom_x[0];
   out_8222410327598512542[1] = delta_x[1] + nom_x[1];
   out_8222410327598512542[2] = delta_x[2] + nom_x[2];
   out_8222410327598512542[3] = delta_x[3] + nom_x[3];
   out_8222410327598512542[4] = delta_x[4] + nom_x[4];
   out_8222410327598512542[5] = delta_x[5] + nom_x[5];
   out_8222410327598512542[6] = delta_x[6] + nom_x[6];
   out_8222410327598512542[7] = delta_x[7] + nom_x[7];
   out_8222410327598512542[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6890329779948884726) {
   out_6890329779948884726[0] = -nom_x[0] + true_x[0];
   out_6890329779948884726[1] = -nom_x[1] + true_x[1];
   out_6890329779948884726[2] = -nom_x[2] + true_x[2];
   out_6890329779948884726[3] = -nom_x[3] + true_x[3];
   out_6890329779948884726[4] = -nom_x[4] + true_x[4];
   out_6890329779948884726[5] = -nom_x[5] + true_x[5];
   out_6890329779948884726[6] = -nom_x[6] + true_x[6];
   out_6890329779948884726[7] = -nom_x[7] + true_x[7];
   out_6890329779948884726[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5330072632657749236) {
   out_5330072632657749236[0] = 1.0;
   out_5330072632657749236[1] = 0;
   out_5330072632657749236[2] = 0;
   out_5330072632657749236[3] = 0;
   out_5330072632657749236[4] = 0;
   out_5330072632657749236[5] = 0;
   out_5330072632657749236[6] = 0;
   out_5330072632657749236[7] = 0;
   out_5330072632657749236[8] = 0;
   out_5330072632657749236[9] = 0;
   out_5330072632657749236[10] = 1.0;
   out_5330072632657749236[11] = 0;
   out_5330072632657749236[12] = 0;
   out_5330072632657749236[13] = 0;
   out_5330072632657749236[14] = 0;
   out_5330072632657749236[15] = 0;
   out_5330072632657749236[16] = 0;
   out_5330072632657749236[17] = 0;
   out_5330072632657749236[18] = 0;
   out_5330072632657749236[19] = 0;
   out_5330072632657749236[20] = 1.0;
   out_5330072632657749236[21] = 0;
   out_5330072632657749236[22] = 0;
   out_5330072632657749236[23] = 0;
   out_5330072632657749236[24] = 0;
   out_5330072632657749236[25] = 0;
   out_5330072632657749236[26] = 0;
   out_5330072632657749236[27] = 0;
   out_5330072632657749236[28] = 0;
   out_5330072632657749236[29] = 0;
   out_5330072632657749236[30] = 1.0;
   out_5330072632657749236[31] = 0;
   out_5330072632657749236[32] = 0;
   out_5330072632657749236[33] = 0;
   out_5330072632657749236[34] = 0;
   out_5330072632657749236[35] = 0;
   out_5330072632657749236[36] = 0;
   out_5330072632657749236[37] = 0;
   out_5330072632657749236[38] = 0;
   out_5330072632657749236[39] = 0;
   out_5330072632657749236[40] = 1.0;
   out_5330072632657749236[41] = 0;
   out_5330072632657749236[42] = 0;
   out_5330072632657749236[43] = 0;
   out_5330072632657749236[44] = 0;
   out_5330072632657749236[45] = 0;
   out_5330072632657749236[46] = 0;
   out_5330072632657749236[47] = 0;
   out_5330072632657749236[48] = 0;
   out_5330072632657749236[49] = 0;
   out_5330072632657749236[50] = 1.0;
   out_5330072632657749236[51] = 0;
   out_5330072632657749236[52] = 0;
   out_5330072632657749236[53] = 0;
   out_5330072632657749236[54] = 0;
   out_5330072632657749236[55] = 0;
   out_5330072632657749236[56] = 0;
   out_5330072632657749236[57] = 0;
   out_5330072632657749236[58] = 0;
   out_5330072632657749236[59] = 0;
   out_5330072632657749236[60] = 1.0;
   out_5330072632657749236[61] = 0;
   out_5330072632657749236[62] = 0;
   out_5330072632657749236[63] = 0;
   out_5330072632657749236[64] = 0;
   out_5330072632657749236[65] = 0;
   out_5330072632657749236[66] = 0;
   out_5330072632657749236[67] = 0;
   out_5330072632657749236[68] = 0;
   out_5330072632657749236[69] = 0;
   out_5330072632657749236[70] = 1.0;
   out_5330072632657749236[71] = 0;
   out_5330072632657749236[72] = 0;
   out_5330072632657749236[73] = 0;
   out_5330072632657749236[74] = 0;
   out_5330072632657749236[75] = 0;
   out_5330072632657749236[76] = 0;
   out_5330072632657749236[77] = 0;
   out_5330072632657749236[78] = 0;
   out_5330072632657749236[79] = 0;
   out_5330072632657749236[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9223035926510894806) {
   out_9223035926510894806[0] = state[0];
   out_9223035926510894806[1] = state[1];
   out_9223035926510894806[2] = state[2];
   out_9223035926510894806[3] = state[3];
   out_9223035926510894806[4] = state[4];
   out_9223035926510894806[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9223035926510894806[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9223035926510894806[7] = state[7];
   out_9223035926510894806[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7463971605514829296) {
   out_7463971605514829296[0] = 1;
   out_7463971605514829296[1] = 0;
   out_7463971605514829296[2] = 0;
   out_7463971605514829296[3] = 0;
   out_7463971605514829296[4] = 0;
   out_7463971605514829296[5] = 0;
   out_7463971605514829296[6] = 0;
   out_7463971605514829296[7] = 0;
   out_7463971605514829296[8] = 0;
   out_7463971605514829296[9] = 0;
   out_7463971605514829296[10] = 1;
   out_7463971605514829296[11] = 0;
   out_7463971605514829296[12] = 0;
   out_7463971605514829296[13] = 0;
   out_7463971605514829296[14] = 0;
   out_7463971605514829296[15] = 0;
   out_7463971605514829296[16] = 0;
   out_7463971605514829296[17] = 0;
   out_7463971605514829296[18] = 0;
   out_7463971605514829296[19] = 0;
   out_7463971605514829296[20] = 1;
   out_7463971605514829296[21] = 0;
   out_7463971605514829296[22] = 0;
   out_7463971605514829296[23] = 0;
   out_7463971605514829296[24] = 0;
   out_7463971605514829296[25] = 0;
   out_7463971605514829296[26] = 0;
   out_7463971605514829296[27] = 0;
   out_7463971605514829296[28] = 0;
   out_7463971605514829296[29] = 0;
   out_7463971605514829296[30] = 1;
   out_7463971605514829296[31] = 0;
   out_7463971605514829296[32] = 0;
   out_7463971605514829296[33] = 0;
   out_7463971605514829296[34] = 0;
   out_7463971605514829296[35] = 0;
   out_7463971605514829296[36] = 0;
   out_7463971605514829296[37] = 0;
   out_7463971605514829296[38] = 0;
   out_7463971605514829296[39] = 0;
   out_7463971605514829296[40] = 1;
   out_7463971605514829296[41] = 0;
   out_7463971605514829296[42] = 0;
   out_7463971605514829296[43] = 0;
   out_7463971605514829296[44] = 0;
   out_7463971605514829296[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7463971605514829296[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7463971605514829296[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7463971605514829296[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7463971605514829296[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7463971605514829296[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7463971605514829296[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7463971605514829296[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7463971605514829296[53] = -9.8000000000000007*dt;
   out_7463971605514829296[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7463971605514829296[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7463971605514829296[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7463971605514829296[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7463971605514829296[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7463971605514829296[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7463971605514829296[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7463971605514829296[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7463971605514829296[62] = 0;
   out_7463971605514829296[63] = 0;
   out_7463971605514829296[64] = 0;
   out_7463971605514829296[65] = 0;
   out_7463971605514829296[66] = 0;
   out_7463971605514829296[67] = 0;
   out_7463971605514829296[68] = 0;
   out_7463971605514829296[69] = 0;
   out_7463971605514829296[70] = 1;
   out_7463971605514829296[71] = 0;
   out_7463971605514829296[72] = 0;
   out_7463971605514829296[73] = 0;
   out_7463971605514829296[74] = 0;
   out_7463971605514829296[75] = 0;
   out_7463971605514829296[76] = 0;
   out_7463971605514829296[77] = 0;
   out_7463971605514829296[78] = 0;
   out_7463971605514829296[79] = 0;
   out_7463971605514829296[80] = 1;
}
void h_25(double *state, double *unused, double *out_4628806759690822080) {
   out_4628806759690822080[0] = state[6];
}
void H_25(double *state, double *unused, double *out_461257227494379088) {
   out_461257227494379088[0] = 0;
   out_461257227494379088[1] = 0;
   out_461257227494379088[2] = 0;
   out_461257227494379088[3] = 0;
   out_461257227494379088[4] = 0;
   out_461257227494379088[5] = 0;
   out_461257227494379088[6] = 1;
   out_461257227494379088[7] = 0;
   out_461257227494379088[8] = 0;
}
void h_24(double *state, double *unused, double *out_537476962457809152) {
   out_537476962457809152[0] = state[4];
   out_537476962457809152[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3096668371307944048) {
   out_3096668371307944048[0] = 0;
   out_3096668371307944048[1] = 0;
   out_3096668371307944048[2] = 0;
   out_3096668371307944048[3] = 0;
   out_3096668371307944048[4] = 1;
   out_3096668371307944048[5] = 0;
   out_3096668371307944048[6] = 0;
   out_3096668371307944048[7] = 0;
   out_3096668371307944048[8] = 0;
   out_3096668371307944048[9] = 0;
   out_3096668371307944048[10] = 0;
   out_3096668371307944048[11] = 0;
   out_3096668371307944048[12] = 0;
   out_3096668371307944048[13] = 0;
   out_3096668371307944048[14] = 1;
   out_3096668371307944048[15] = 0;
   out_3096668371307944048[16] = 0;
   out_3096668371307944048[17] = 0;
}
void h_30(double *state, double *unused, double *out_281862646350510226) {
   out_281862646350510226[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6455433113997237667) {
   out_6455433113997237667[0] = 0;
   out_6455433113997237667[1] = 0;
   out_6455433113997237667[2] = 0;
   out_6455433113997237667[3] = 0;
   out_6455433113997237667[4] = 1;
   out_6455433113997237667[5] = 0;
   out_6455433113997237667[6] = 0;
   out_6455433113997237667[7] = 0;
   out_6455433113997237667[8] = 0;
}
void h_26(double *state, double *unused, double *out_7990611940570041035) {
   out_7990611940570041035[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4202760546368435312) {
   out_4202760546368435312[0] = 0;
   out_4202760546368435312[1] = 0;
   out_4202760546368435312[2] = 0;
   out_4202760546368435312[3] = 0;
   out_4202760546368435312[4] = 0;
   out_4202760546368435312[5] = 0;
   out_4202760546368435312[6] = 0;
   out_4202760546368435312[7] = 1;
   out_4202760546368435312[8] = 0;
}
void h_27(double *state, double *unused, double *out_4025490875014344563) {
   out_4025490875014344563[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4280669802196812756) {
   out_4280669802196812756[0] = 0;
   out_4280669802196812756[1] = 0;
   out_4280669802196812756[2] = 0;
   out_4280669802196812756[3] = 1;
   out_4280669802196812756[4] = 0;
   out_4280669802196812756[5] = 0;
   out_4280669802196812756[6] = 0;
   out_4280669802196812756[7] = 0;
   out_4280669802196812756[8] = 0;
}
void h_29(double *state, double *unused, double *out_388041346760322213) {
   out_388041346760322213[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2567307075327261723) {
   out_2567307075327261723[0] = 0;
   out_2567307075327261723[1] = 1;
   out_2567307075327261723[2] = 0;
   out_2567307075327261723[3] = 0;
   out_2567307075327261723[4] = 0;
   out_2567307075327261723[5] = 0;
   out_2567307075327261723[6] = 0;
   out_2567307075327261723[7] = 0;
   out_2567307075327261723[8] = 0;
}
void h_28(double *state, double *unused, double *out_3267640729853525753) {
   out_3267640729853525753[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2515091941742268851) {
   out_2515091941742268851[0] = 1;
   out_2515091941742268851[1] = 0;
   out_2515091941742268851[2] = 0;
   out_2515091941742268851[3] = 0;
   out_2515091941742268851[4] = 0;
   out_2515091941742268851[5] = 0;
   out_2515091941742268851[6] = 0;
   out_2515091941742268851[7] = 0;
   out_2515091941742268851[8] = 0;
}
void h_31(double *state, double *unused, double *out_6148778611774655792) {
   out_6148778611774655792[0] = state[8];
}
void H_31(double *state, double *unused, double *out_430611265617418660) {
   out_430611265617418660[0] = 0;
   out_430611265617418660[1] = 0;
   out_430611265617418660[2] = 0;
   out_430611265617418660[3] = 0;
   out_430611265617418660[4] = 0;
   out_430611265617418660[5] = 0;
   out_430611265617418660[6] = 0;
   out_430611265617418660[7] = 0;
   out_430611265617418660[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_8222410327598512542) {
  err_fun(nom_x, delta_x, out_8222410327598512542);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6890329779948884726) {
  inv_err_fun(nom_x, true_x, out_6890329779948884726);
}
void car_H_mod_fun(double *state, double *out_5330072632657749236) {
  H_mod_fun(state, out_5330072632657749236);
}
void car_f_fun(double *state, double dt, double *out_9223035926510894806) {
  f_fun(state,  dt, out_9223035926510894806);
}
void car_F_fun(double *state, double dt, double *out_7463971605514829296) {
  F_fun(state,  dt, out_7463971605514829296);
}
void car_h_25(double *state, double *unused, double *out_4628806759690822080) {
  h_25(state, unused, out_4628806759690822080);
}
void car_H_25(double *state, double *unused, double *out_461257227494379088) {
  H_25(state, unused, out_461257227494379088);
}
void car_h_24(double *state, double *unused, double *out_537476962457809152) {
  h_24(state, unused, out_537476962457809152);
}
void car_H_24(double *state, double *unused, double *out_3096668371307944048) {
  H_24(state, unused, out_3096668371307944048);
}
void car_h_30(double *state, double *unused, double *out_281862646350510226) {
  h_30(state, unused, out_281862646350510226);
}
void car_H_30(double *state, double *unused, double *out_6455433113997237667) {
  H_30(state, unused, out_6455433113997237667);
}
void car_h_26(double *state, double *unused, double *out_7990611940570041035) {
  h_26(state, unused, out_7990611940570041035);
}
void car_H_26(double *state, double *unused, double *out_4202760546368435312) {
  H_26(state, unused, out_4202760546368435312);
}
void car_h_27(double *state, double *unused, double *out_4025490875014344563) {
  h_27(state, unused, out_4025490875014344563);
}
void car_H_27(double *state, double *unused, double *out_4280669802196812756) {
  H_27(state, unused, out_4280669802196812756);
}
void car_h_29(double *state, double *unused, double *out_388041346760322213) {
  h_29(state, unused, out_388041346760322213);
}
void car_H_29(double *state, double *unused, double *out_2567307075327261723) {
  H_29(state, unused, out_2567307075327261723);
}
void car_h_28(double *state, double *unused, double *out_3267640729853525753) {
  h_28(state, unused, out_3267640729853525753);
}
void car_H_28(double *state, double *unused, double *out_2515091941742268851) {
  H_28(state, unused, out_2515091941742268851);
}
void car_h_31(double *state, double *unused, double *out_6148778611774655792) {
  h_31(state, unused, out_6148778611774655792);
}
void car_H_31(double *state, double *unused, double *out_430611265617418660) {
  H_31(state, unused, out_430611265617418660);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
