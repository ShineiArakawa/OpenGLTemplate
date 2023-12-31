#pragma once
#ifndef _BOX_H_
#define _BOX_H_

#include <Model/Primitives.hpp>
#include <OpenGL.hpp>
#include <Util/ObjectLoader.hpp>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class Box : public Primitives {
 private:
  float _offsetX;
  float _offsetY;
  float _offsetZ;
  float _scaleX;
  float _scaleY;
  float _scaleZ;
  GLuint _vaoId;
  GLuint _vertexBufferId;
  GLuint _indexBufferId;
  // clang-format off
  inline static const glm::vec3 positions[8] = {
      glm::vec3(-1.0f, -1.0f, -1.0f),
      glm::vec3(1.0f, -1.0f, -1.0f),
      glm::vec3(-1.0f,  1.0f, -1.0f),
      glm::vec3(-1.0f, -1.0f,  1.0f),
      glm::vec3(1.0f,  1.0f, -1.0f),
      glm::vec3(-1.0f,  1.0f,  1.0f),
      glm::vec3(1.0f, -1.0f,  1.0f),
      glm::vec3(1.0f,  1.0f,  1.0f)
  };
  inline static const glm::vec3 colors[6] = {
      glm::vec3(1.0f, 0.0f, 0.0f), 
      glm::vec3(0.0f, 1.0f, 0.0f), 
      glm::vec3(0.0f, 0.0f, 1.0f), 
      glm::vec3(1.0f, 1.0f, 0.0f), 
      glm::vec3(0.0f, 1.0f, 1.0f), 
      glm::vec3(1.0f, 0.0f, 1.0f)
  };
  inline static const glm::vec3 textureCoords[8] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f)
  };
  inline static const unsigned int faces[12][3] = {
      { 7, 4, 1 }, { 7, 1, 6 },
      { 2, 4, 7 }, { 2, 7, 5 },
      { 5, 7, 6 }, { 5, 6, 3 },
      { 4, 2, 0 }, { 4, 0, 1 },
      { 3, 6, 1 }, { 3, 1, 0 },
      { 2, 5, 3 }, { 2, 3, 0 }
  };
  // clang-format on

 protected:
  // nothing
 public:
  // nothing

 private:
  // nothing
 protected:
  // nothing
 public:
  Box(const float offsetX, const float offsetY, const float offsetZ, const float scaleX, const float scaleY, const float scaleZ);
  ~Box();

  void update(){};
  void initVAO();
  void paintGL(const glm::mat4& mvpMat);
};
#endif
