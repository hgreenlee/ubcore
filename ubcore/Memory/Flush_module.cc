////////////////////////////////////////////////////////////////////////
// Class:       Flush
// Plugin Type: producer
// File:        Flush_module.cc
//
// Purpose: Removed cached data products read from an input file from memory.
//
// FCL parameters: None
//
// Generated at Mon Aug  4 13:55:27 2025 by Herbert Greenlee using cetskelgen
// from cetlib version 3.18.02.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Framework/Principal/ProductRetriever.h"
#include "art/Framework/Principal/EventPrincipal.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include <memory>

// Same members as art::Event, but public.

struct HackEvent : public art::ProductRetriever {
  std::optional<art::ProductInserter> inserter_;
  art::EventPrincipal const& eventPrincipal_;
  art::SubRun const subRun_;
};


class Flush : public art::EDProducer {
public:
  explicit Flush(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  Flush(Flush const&) = delete;
  Flush(Flush&&) = delete;
  Flush& operator=(Flush const&) = delete;
  Flush& operator=(Flush&&) = delete;

  // Required functions.
  void produce(art::Event& e) override;

private:

  // Declare member data here.

};

// Constructor.

Flush::Flush(fhicl::ParameterSet const& p) : EDProducer{p}
{
  //std::cout << "Module Flush constructor called." << std::endl;
}

void Flush::produce(art::Event& e)
{
  std::cout << "Module Flush produce method called." << std::endl;

  HackEvent& he = reinterpret_cast<HackEvent&>(e);
  const art::EventPrincipal& ep = he.eventPrincipal_;

  // In the following loop, EventPrincipal as acting like collecion
  // std::map<art::ProductID, std::unique_ptr<art::Group>>

  for(auto const& g : ep) {
    art::Group& gr = *(g.second);
    const art::BranchDescription& pd = gr.productDescription();
    if(pd.present() && !pd.produced()) {
      std::cout << "Uncaching product type = " << pd.friendlyClassName() << ", " << pd.inputTag() << std::endl;
      gr.removeCachedProduct();
    }
  }
}

DEFINE_ART_MODULE(Flush)
