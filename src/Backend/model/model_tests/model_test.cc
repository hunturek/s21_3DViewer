#include "test.h"

TEST(Model, amount_vert_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  EXPECT_EQ(3618, model_ptr->matrix.get_rows());
}

TEST(Model, amount_face_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";
  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  EXPECT_EQ((unsigned long)3442, model_ptr->facets.size());
}

TEST(Model, vert_fill_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";
  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  EXPECT_NEAR(0.407673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.571387, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(0.205197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, face_fill_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";
  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  EXPECT_EQ(4, model_ptr->facets[5].size());
  EXPECT_EQ(93, model_ptr->facets[5][0]);
  EXPECT_EQ(94, model_ptr->facets[5][1]);
  EXPECT_EQ(88, model_ptr->facets[5][2]);
  EXPECT_EQ(89, model_ptr->facets[5][3]);
}

TEST(Model, minmax_ranges_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  EXPECT_NEAR(-2.712309, model_ptr->range_x[0], 1e-6);
  EXPECT_NEAR(2.712309, model_ptr->range_x[1], 1e-6);
  EXPECT_NEAR(-3.294219, model_ptr->range_y[0], 1e-6);
  EXPECT_NEAR(2.597942, model_ptr->range_y[1], 1e-6);
  EXPECT_NEAR(-1.111950, model_ptr->range_z[0], 1e-6);
  EXPECT_NEAR(1.111950, model_ptr->range_z[1], 1e-6);
}

TEST(Model, move_x_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Movement(1.5, 'x');

  EXPECT_NEAR(1.907673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.571387, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(0.205197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, move_y_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Movement(1.5, 'y');
  EXPECT_NEAR(0.407673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(0.928613, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(0.205197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, move_z_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Movement(1.5, 'z');
  EXPECT_NEAR(0.407673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.571387, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(1.705197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, rot_x_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Rot(90, 'x');

  EXPECT_NEAR(0.407673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.205197, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(-0.571387, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, rot_y_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Rot(90, 'y');
  EXPECT_NEAR(0.205197, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.571387, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(-0.407673, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, rot_z_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Rot(90, 'z');
  EXPECT_NEAR(0.571387, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(0.407673, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(0.205197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, mult_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->Mult(10);

  EXPECT_NEAR(4.07673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-5.71387, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(2.05197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, frames_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->ResizeFrames(5);
  EXPECT_NEAR(0.69189, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.969741, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(0.348254, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, central_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normal.obj";

  s21::BuilderFromObjFile build(filename);
  std::shared_ptr<s21::ProductModel> model_ptr = nullptr;

  EXPECT_NO_THROW(build.CreateModel());
  model_ptr = build.GetProductModel();

  model_ptr->CenterFrames();

  EXPECT_NEAR(0.407673, model_ptr->matrix(3610, 0), 1e-6);
  EXPECT_NEAR(-0.223248, model_ptr->matrix(3610, 1), 1e-6);
  EXPECT_NEAR(0.205197, model_ptr->matrix(3610, 2), 1e-6);
}

TEST(Model, file_err_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/normalin.obj";
  s21::BuilderFromObjFile build(filename);

  EXPECT_ANY_THROW(build.CreateModel());
}

TEST(Model, face_err_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/nenormal.obj";
  s21::BuilderFromObjFile build(filename);

  EXPECT_ANY_THROW(build.CreateModel());
}

TEST(Model, empty_file_test) {
  const char *filename =
      "Backend/model/model_tests/examples_for_tests/empty.obj";
  s21::BuilderFromObjFile build(filename);

  EXPECT_ANY_THROW(build.CreateModel());
}

TEST(Observer, Attach) {
  s21::Subject subj;

  class ConcreteObserver : public s21::IObserver {
   public:
    void Update() override {
      std::cout << "ConcreteObserver: Updated!" << std::endl;
    }
  } obj;

  subj.Attach(&obj);
  EXPECT_EQ(1, subj.HowManyObserver());
}

TEST(Observer, Detach) {
  s21::Subject subj;

  class ConcreteObserver : public s21::IObserver {
   public:
    void Update() override {
      std::cout << "ConcreteObserver: Updated!" << std::endl;
    }
  } obj;

  subj.Attach(&obj);
  subj.Detach(&obj);
  EXPECT_EQ(0, subj.HowManyObserver());
}

TEST(Observer, Notify) {
  s21::Subject subj;

  class ConcreteObserver : public s21::IObserver {
   public:
    int i = 0;
    void Update() override { i = 1; }
  } obj;

  subj.Attach(&obj);
  subj.Notify();
  EXPECT_EQ(1, obj.i);
}