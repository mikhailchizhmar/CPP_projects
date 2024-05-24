/**
 * @file obj3d.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief obj3d class header
 * @version 0.1
 * @date 2023-11-26
 * @copyright Copyright (c) 2023
 */
#include "./obj3d.h"

#include <cstring>

namespace s21 {

FILE* Obj3d::openFile_(const char* name) {
  FILE* f = fopen(name, "r");
  if (!f) fprintf(stdout, "s21_3dviewer: %s: no such file\n", name);
  return f;
}

bool Obj3d::loadFromFile(const char* fname) {
  return read_obj_(openFile_(fname));
}

void Obj3d::initObj3d_() {
  total_indices = 0;
  bounds = {0, 0, 0, 0, 0, 0};
  centers = {0, 0, 0};
}

bool Obj3d::read_obj_(FILE* f) {
  free_obj3d_();
  initObj3d_();
  bool status = false;
  status = fill_obj3d_(f);
  fclose(f);
  return status;
}

void Obj3d::free_obj3d_() {
  if (vtx_arr.size()) vtx_arr.clear();
  if (polygons.size()) polygons.clear();
}

int Obj3d::fill_obj3d_(FILE* f) {
  char buffer[BUFF_SIZE] = {0};
  bool first_line{true};
  fseek(f, 0, SEEK_SET); /* to begin of file*/
  unsigned int i{};
  bool status{false};
  char* endptr = buffer + 1;
  while (fgets(buffer, BUFF_SIZE, f)) {
    endptr = buffer + 1;
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      vtx_arr.push_back(strtod(endptr, &endptr));
      vtx_arr.push_back(strtod(endptr, &endptr));
      vtx_arr.push_back(strtod(endptr, &endptr));
      parseMaxMin_(vtx_arr[i], vtx_arr[i + 1], vtx_arr[i + 2], first_line);
      first_line = false;
      i += 3;
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      status = fill_facets_(buffer);
    }
  }
  return status;
}

bool Obj3d::fill_facets_(const char* buffer) {
  unsigned int count = count_vtx_of_facet_(buffer);
  total_indices += count;
  if (count > 0) parse_vertices_(buffer);
  return (count > 0) ? true : false;
}

void Obj3d::parseMaxMin_(double x, double y, double z, int first_line) {
  if (!first_line) {
    compareNums_(bounds.x_min, bounds.x_max, x);
    compareNums_(bounds.y_min, bounds.y_max, y);
    compareNums_(bounds.z_min, bounds.z_max, z);
  } else {
    bounds = {x, x, y, y, z, z};
  }
}

void Obj3d::compareNums_(double& min, double& max, double comparable) {
  if (max < comparable) max = comparable;
  if (min > comparable) min = comparable;
}

unsigned int Obj3d::count_vtx_of_facet_(const char* buffer) {
  char str[255] = {0};
  unsigned count = 0;
  buffer += 2; /* skip first f_ */
  while (*buffer && sscanf(buffer, "%s", str)) {
    unsigned int length = 0;
    length = strlen(str) + 1;
    buffer += length;
    if (length > 1) ++count; /*skip spaces*/
    strcpy(str, "");
  }
  return count;
}

unsigned int Obj3d::parse_vertices_(const char* buffer) {
  char str[255] = {0};
  unsigned int count = 0;
  char* endptr = nullptr;
  buffer += 2; /* skip first f_ */
  std::vector<unsigned int> vertexes;
  while (*buffer) {
    unsigned int length = 0;
    sscanf(buffer, "%s", str);
    length = strlen(str) + 1;
    buffer += length;
    endptr = str;
    if (length > 1) { /*skip spaces*/
      /* -1 because in obj.file indexes of vertices starts from 1 */
      /* and in openGL from zero */
      vertexes.push_back(((unsigned int)strtod(endptr, &endptr)) - 1);
      ++count;
    }
    strcpy(str, "");
  }
  polygons.push_back(vertexes);
  return count;
}

void Obj3d::centerObj() {
  centers.x_center = centersFormula_(bounds.x_min, bounds.x_max);
  centers.y_center = centersFormula_(bounds.y_min, bounds.y_max);
  centers.z_center = centersFormula_(bounds.z_min, bounds.z_max);
  for (auto i{0LU}, end{vtx_arr.size()}; i < end; i += 3) {
    vtx_arr[i] -= centers.x_center;
    vtx_arr[i + 1] -= centers.y_center;
    vtx_arr[i + 2] -= centers.z_center;
  }
}

double Obj3d::centersFormula_(double& minVal, double& maxVal) {
  double center = minVal + (maxVal - minVal) / 2;
  minVal -= center;
  maxVal -= center;
  return center;
}

const double* Obj3d::getVertexes() const noexcept { return vtx_arr.data(); }

std::vector<std::vector<unsigned int>>& Obj3d::GetPolygons() {
  return polygons;
}

axis_t Obj3d::GetBounds() const noexcept { return bounds; }

unsigned int Obj3d::GetVtxCount() { return vtx_arr.size() / 3; }

unsigned int Obj3d::GetFctCount() { return polygons.size(); }

unsigned int Obj3d::GetFctVtx(unsigned int i) { return polygons[i].size(); }

unsigned int Obj3d::GetTotalIndices() { return total_indices; }

std::vector<double>* Obj3d::setVertexes() noexcept { return &vtx_arr; };

axis_t& Obj3d::SetBounds() noexcept { return bounds; };

}  // namespace s21
