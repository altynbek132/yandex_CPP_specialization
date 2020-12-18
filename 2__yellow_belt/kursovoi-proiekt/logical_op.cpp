//
// Created by Addmin on 15.12.2020.
//

#include "logical_op.h"
#include <stdexcept>

bool PerformLogicalOperation(const LogicalOperation &logical_operation, bool lhs, bool rhs) {
    switch (logical_operation) {
        case LogicalOperation::Or: {
            return lhs || rhs;
        }
        case LogicalOperation::And: {
            return lhs && rhs;
        }
        default: {
            throw std::logic_error("unknown logical operation");
        }
    }
}
