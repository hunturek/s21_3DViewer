#include "./s21_builder.h"

#include <cstring>

namespace s21 {

void BuilderFromObjFile::ObjCounter() {
  std::FILE *file = nullptr;
  file = std::fopen(file_name, "r");

  if (!file) throw std::ios_base::failure("file does not open");

  char *str = nullptr;
  size_t len = 0;
  int vertex_counter = 0;
  int facets_counter = 0;

  while (getline(&str, &len, file) != -1) {
    if (*str == 'v' && *(str + 1) == ' ') ++vertex_counter;
    if (*str == 'f' && *(str + 1) == ' ') ++facets_counter;
  }
  std::fclose(file);
  if (str) free(str);

  if (vertex_counter == 0) throw std::ios_base::failure("no vertex in file");

  model_ptr->facets.resize(facets_counter);
  model_ptr->matrix.set_rows(vertex_counter);
}

void BuilderFromObjFile::MatrixFill() {
  int flag = 0;
  std::FILE *file = std::fopen(file_name, "r");
  if (!file) throw std::ios_base::failure("file does not open");

  char *str = nullptr;
  size_t len = 0;
  int vertex_counter = 0, facets_counter = 0;
  char *istr = NULL;

  while (getline(&str, &len, file) != -1 && flag == 0) {
    if (*str == 'v' && *(str + 1) == ' ') {
      strtok(str, " \n");
      istr = strtok(NULL, " \n");
      model_ptr->matrix(vertex_counter, 0) = atof(istr);  // x
      istr = strtok(NULL, " \n");
      model_ptr->matrix(vertex_counter, 1) = atof(istr);  // y
      istr = strtok(NULL, " \n");
      model_ptr->matrix(vertex_counter, 2) = atof(istr);  // z
      istr = NULL;
      MinMax(vertex_counter);
      ++vertex_counter;
    }
    if (*str == 'f' && *(str + 1) == ' ') {
      int tmp = 0;
      for (int i = 0; *(str + i) != '\n'; ++i)
        if (*(str + i) == ' ') ++tmp;
      model_ptr->facets[facets_counter].resize(tmp);

      tmp = 0;
      strtok(str, " \n");
      istr = strtok(NULL, " \n");
      while (istr != NULL && flag == 0) {
        if (!sscanf(istr, "%d", &(model_ptr->facets[facets_counter][tmp])))
          flag = 1;
        if (model_ptr->facets[facets_counter][tmp] >
                model_ptr->matrix.get_rows() ||
            model_ptr->facets[facets_counter][tmp] < 0)
          flag = 1;
        else
          model_ptr->facets[facets_counter][tmp] -= 1;
        ++tmp;
        istr = strtok(NULL, " \n");
      }
      ++facets_counter;
    }
  }
  std::fclose(file);
  if (str) free(str);
  if (flag) throw std::ios_base::failure("smth with file");
}

void BuilderFromObjFile::MinMax(int vertex_counter) {
  if (model_ptr->matrix(vertex_counter, 0) < model_ptr->range_x[0])
    model_ptr->range_x[0] = model_ptr->matrix(vertex_counter, 0);
  if (model_ptr->matrix(vertex_counter, 0) > model_ptr->range_x[1])
    model_ptr->range_x[1] = model_ptr->matrix(vertex_counter, 0);

  if (model_ptr->matrix(vertex_counter, 1) < model_ptr->range_y[0])
    model_ptr->range_y[0] = model_ptr->matrix(vertex_counter, 1);
  if (model_ptr->matrix(vertex_counter, 1) > model_ptr->range_y[1])
    model_ptr->range_y[1] = model_ptr->matrix(vertex_counter, 1);

  if (model_ptr->matrix(vertex_counter, 2) < model_ptr->range_z[0])
    model_ptr->range_z[0] = model_ptr->matrix(vertex_counter, 2);
  if (model_ptr->matrix(vertex_counter, 2) > model_ptr->range_z[1])
    model_ptr->range_z[1] = model_ptr->matrix(vertex_counter, 2);
}

void BuilderFromObjFile::CreateModel() {
  Reset();
  model_ptr = std::make_shared<ProductModel>();
  ObjCounter();
  MatrixFill();
}
}  // namespace s21
