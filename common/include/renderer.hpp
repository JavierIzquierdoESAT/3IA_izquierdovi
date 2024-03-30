#pragma once
#include "generator.hpp"

class Generator;

class Renderer{
public:
  Renderer() = default;

  void FetchRenderer(const Generator& grid);
  void render() const;

private:
  
  
};