//
// Created by Addmin on 15.12.2020.
//

#pragma once

enum LogicalOperation {
  Or,
  And
};


bool PerformLogicalOperation(const LogicalOperation &logical_operation, bool lhs, bool rhs);
