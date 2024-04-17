#ifndef CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_STRATEGY_OPTIONS_H_
#define CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_STRATEGY_OPTIONS_H_

#include "gl_class.h"

class gl_class;

namespace s21 {

class StrategyOptProjection {
 public:
  virtual ~StrategyOptProjection() = default;
  virtual void projection(gl_class &gl) = 0;
};

class StrategyOptVertices {
 public:
  virtual ~StrategyOptVertices() = default;
  virtual void optionVertices(gl_class &gl) = 0;
};

class StrategyOptEdges {
 public:
  virtual ~StrategyOptEdges() = default;
  virtual void optionEdge(gl_class &gl) = 0;
};

class Parallel : public StrategyOptProjection {
 public:
  void projection(gl_class &gl) override;
};

class Central : public StrategyOptProjection {
 public:
  void projection(gl_class &gl) override;
};

class NoneVertices : public StrategyOptVertices {
 public:
  void optionVertices(gl_class &gl) override;
};

class CircleVertices : public StrategyOptVertices {
 public:
  void optionVertices(gl_class &gl) override;
};

class SquareVertices : public StrategyOptVertices {
 public:
  void optionVertices(gl_class &gl) override;
};

class SolidEdge : public StrategyOptEdges {
 public:
  void optionEdge(gl_class &gl) override;
};

class DashEdge : public StrategyOptEdges {
 public:
  void optionEdge(gl_class &gl) override;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_3DVIEWER_VIEW_STRATEGY_OPTIONS_H_
