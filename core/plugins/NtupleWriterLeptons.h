#pragma once

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "UHH2/core/plugins/NtupleWriterModule.h"

namespace uhh2 {

class NtupleWriterElectrons: public NtupleWriterModule {
public:
    
    struct Config: public NtupleWriterModule::Config {     
      edm::InputTag pv_src;
      std::vector<std::string> id_keys;

      // inherit constructor does not work yet :-(
      Config(uhh2::Context & ctx_, edm::ConsumesCollector && cc_, const edm::InputTag & src_,
             const std::string & dest_, const std::string & dest_branchname_ = ""):
        NtupleWriterModule::Config(ctx_, std::move(cc_), src_, dest_, dest_branchname_) {}
    };

    explicit NtupleWriterElectrons(Config & cfg, bool set_electrons_member, const bool save_source_cands=0);

    virtual void process(const edm::Event &, uhh2::Event &, const edm::EventSetup& iSetup);

    virtual ~NtupleWriterElectrons();
private:
    edm::EDGetToken src_token;
    edm::EDGetToken pv_token;
    std::vector<std::string> IDtag_keys;
    Event::Handle<std::vector<Electron>> handle; // main handle to write output to
    boost::optional<Event::Handle<std::vector<Electron>>> electrons_handle; // handle of name "electrons" in case set_electrons_member is true

    bool save_source_candidates_;
};

class NtupleWriterMuons: public NtupleWriterModule {
public:
    
    struct Config: public NtupleWriterModule::Config {
      edm::InputTag pv_src;

      // inherit constructor does not work yet :-(
      Config(uhh2::Context & ctx_, edm::ConsumesCollector && cc_, const edm::InputTag & src_,
             const std::string & dest_, const std::string & dest_branchname_ = ""):
        NtupleWriterModule::Config(ctx_, std::move(cc_), src_, dest_, dest_branchname_) {}
    };

    explicit NtupleWriterMuons(Config & cfg, bool set_muons_member, const bool save_source_cands=0);

    virtual void process(const edm::Event &, uhh2::Event &, const edm::EventSetup& iSetup);

    virtual ~NtupleWriterMuons();
private:
    edm::EDGetToken src_token;
    edm::EDGetToken pv_token;
    Event::Handle<std::vector<Muon>> handle;
    boost::optional<Event::Handle<std::vector<Muon>>> muons_handle;

    bool save_source_candidates_;
};

class NtupleWriterTaus: public NtupleWriterModule {
public:

    explicit NtupleWriterTaus(Config & cfg, bool set_taus_member);

    virtual void process(const edm::Event &, uhh2::Event &, const edm::EventSetup& iSetup);

    virtual ~NtupleWriterTaus();
private:
    double ptmin, etamax;
    edm::EDGetToken src_token;
    Event::Handle<std::vector<Tau>> handle;
    boost::optional<Event::Handle<std::vector<Tau>>> taus_handle;
};

}


