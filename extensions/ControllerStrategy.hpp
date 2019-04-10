#include <boost/random/mersenne_twister.hpp>
#include "face/face.hpp"
#include "fw/strategy.hpp"
#include "fw/algorithm.hpp"

namespace nfd {
namespace fw {

class ControllerStrategy : public Strategy {
public:
  ControllerStrategy(Forwarder& forwarder, const Name& name = getStrategyName());

  virtual ~ControllerStrategy() override;

  virtual void
  afterReceiveInterest(const Face& inFace, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry) override;

  static const Name&
  getStrategyName();

protected:
  boost::random::mt19937 m_randomGenerator;
};

} // namespace fw
} // namespace nfd