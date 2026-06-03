#pragma once

#include <variant>
#include <memory>
#include <utility>
#include "Overlaoded.hpp"

struct Expr;

struct Literal {
	int value;
};

struct Add {
	std::unique_ptr<Expr> left, right;
};

struct Mul {
	std::unique_ptr<Expr> left, right;
};

struct Neg {
	std::unique_ptr<Expr> expr;
};

struct Expr {
	using Variant = std::variant<Literal, Mul, Add, Neg>;
	Variant node;

	template<typename T>
	Expr(T t) : node(std::move(t)) {}
};

inline int eval(const Expr& expr) {
	return std::visit(overloaded{
		[](const Literal& l) {
			return l.value;
		},
		[](const Add& a) {
			return eval(*a.left) + eval(*a.right);
		},
		[](const Mul& m) {
			return eval(*m.left) * eval(*m.right);
		},
		[](const Neg& n) {
			return -eval(*n.expr);
		}
	}, expr.node);
}
