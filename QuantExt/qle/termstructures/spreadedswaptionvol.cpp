/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/* This file is supposed to be part of the QuantLib library eventually,
   in the meantime we provide is as part of the QuantExt library. */

/*
 Copyright (C) 2008 Ferdinando Ametrano
 Copyright (C) 2007 Giorgio Facchinetti

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*
  Copyright (C) 2016 Quaternion Risk Management Ltd.
  All rights reserved.
*/

#include <qle/termstructures/spreadedswaptionvol.hpp>

#include <ql/termstructures/volatility/spreadedsmilesection.hpp>
#include <ql/quote.hpp>

namespace QuantLib {

    SpreadedSwaptionVolatility::SpreadedSwaptionVolatility(
                            const Handle<SwaptionVolatilityStructure>& baseVol,
                            const Handle<Quote>& spread)
    : SwaptionVolatilityStructure(baseVol->businessDayConvention(),
                                  baseVol->dayCounter()),
      baseVol_(baseVol), spread_(spread) {
          enableExtrapolation(baseVol->allowsExtrapolation());
          registerWith(baseVol_);
          registerWith(spread_);
    }

    boost::shared_ptr<SmileSection>
    SpreadedSwaptionVolatility::smileSectionImpl(const Date& d,
                                                 const Period& swapT) const {
        boost::shared_ptr<SmileSection> baseSmile =
            baseVol_->smileSection(d, swapT, true);
        return boost::shared_ptr<SmileSection>(new
            SpreadedSmileSection(baseSmile, spread_));
    }

    boost::shared_ptr<SmileSection>
    SpreadedSwaptionVolatility::smileSectionImpl(Time optionTime,
                                                 Time swapLength) const {
        boost::shared_ptr<SmileSection> baseSmile =
            baseVol_->smileSection(optionTime, swapLength, true);
        return boost::shared_ptr<SmileSection>(new
            SpreadedSmileSection(baseSmile, spread_));
    }

    Volatility SpreadedSwaptionVolatility::volatilityImpl(const Date& d,
                                                          const Period& p,
                                                          Rate strike) const {
        return baseVol_->volatility(d, p, strike, true) + spread_->value();
    }

    Volatility SpreadedSwaptionVolatility::volatilityImpl(Time t,
                                                          Time l,
                                                          Rate strike) const {
        return baseVol_->volatility(t, l, strike, true) + spread_->value();
    }

}
