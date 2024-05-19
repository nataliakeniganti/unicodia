// My header
#include "UcRequest.h"

uc::MultiResult uc::doRequest(const Request& rq)
{
    uc::MultiResult r(uc::ReplyStyle::GROUPED, rq.ecVersion());

    const uc::Block* oldBlock = nullptr;
    uc::SearchGroup* lastGroup = nullptr;
    if (rq.hasChars()) {
        for (const auto& cp : uc::cpInfo) {
            if (rq.isOk(cp)) {
                auto* newBlock = &cp.block();
                if (newBlock != oldBlock) {
                    lastGroup = &r.groups.emplace_back();
                    lastGroup->block = newBlock;
                    oldBlock = newBlock;
                }
                lastGroup->lines.emplace_back(cp);
            }
        }
    }

    if (rq.hasEmoji()) {
        /// @todo [future] search for emoji
    }

    return r;
}


///// FieldRequest /////////////////////////////////////////////////////////////


bool uc::FieldRequest::isOk(const Cp& cp) const
{
    // Version
    if (fields.ecVersion != uc::EcVersion::NO_VALUE && fields.ecVersion != cp.ecVersion)
        return false;
    // Script
    if (fields.ecScript != uc::EcScript::NO_VALUE && fields.ecScript != cp.ecScript)
        return false;
    // Category
    if (fields.ecCategory != uc::EcCategory::NO_VALUE && fields.ecCategory != cp.ecCategory)
        return false;
    return true;
}
