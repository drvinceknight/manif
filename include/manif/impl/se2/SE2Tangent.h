#ifndef _MANIF_MANIF_SE2TANGENT_H_
#define _MANIF_MANIF_SE2TANGENT_H_

#include "manif/impl/so2/SE2Tangent_base.h"

#include <Eigen/Core>

namespace manif
{
namespace internal
{

// Traits specialization

template <typename _Scalar>
struct traits<SE2Tangent<_Scalar>>
{
  template <typename T>
  using TangentTemplate = SE2Tangent<T>;

  using Scalar = _Scalar;

  using Manifold = SE2<_Scalar>;
  using Tangent  = SE2Tangent<_Scalar>;

  using Base = SE2TangentBase<_Scalar>;

  static constexpr int Dim     = ManifoldProperties<Base>::Dim;
  static constexpr int DoF     = ManifoldProperties<Base>::DoF;
  static constexpr int RepSize = DoF;

  using DataType = Eigen::Matrix<Scalar, DoF, 1>;
  using Jacobian = Eigen::Matrix<Scalar, DoF, DoF>;
  using LieType  = Eigen::Matrix<Scalar, 3, 3>;
};

} /* namespace internal */
} /* namespace manif */

namespace manif
{

///////////////
///         ///
/// Tangent ///
///         ///
///////////////

template <typename _Scalar>
struct SE2Tangent : SE2TangentBase<SE2Tangent<_Scalar>>
{
private:

  using Base = SO2TangentBase<SO2Tangent<_Scalar>>;
  using Type = SO2Tangent<_Scalar>;

public:

  MANIF_TANGENT_TYPEDEF

  SE2Tangent() = default;

  SE2Tangent(const DataType& v);
  SE2Tangent(const Scalar x, const Scalar y, const Scalar theta);

  /// Tangent common API

  const DataType& coeffs() const;

  MANIF_INHERIT_TANGENT_API
  MANIF_INHERIT_TANGENT_OPERATOR

  /// SE2Tangent specific API

  using Base::angle;

protected:

  friend class TangentBase<SE2Tangent<Scalar>>;
  DataType& coeffs_nonconst();

  DataType data_;
};

MANIF_EXTRA_TANGENT_TYPEDEF(SE2Tangent);

template <typename _Scalar>
SE2Tangent<_Scalar>::SE2Tangent(const DataType& theta)
  : data_(theta)
{
  //
}

template <typename _Scalar>
SE2Tangent<_Scalar>::SE2Tangent(const Scalar x,
                                const Scalar y,
                                const Scalar theta)
  : SE2Tangent(DataType(x, y, theta))
{
  //
}

template <typename _Scalar>
typename SE2Tangent<_Scalar>::DataType&
SE2Tangent<_Scalar>::coeffs_nonconst()
{
  return data_;
}

template <typename _Scalar>
const typename SE2Tangent<_Scalar>::DataType&
SE2Tangent<_Scalar>::coeffs() const
{
  return data_;
}

} /* namespace manif */

#endif /* _MANIF_MANIF_SE2TANGENT_H_ */
