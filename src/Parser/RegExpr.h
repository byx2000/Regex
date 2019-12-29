#pragma once

#include "../NFA/NFAGraph.h"

#include <memory>

class Node
{
public:
	virtual std::string toString() const = 0;
	virtual NFAGraph getNFAGraph() const = 0;
	virtual ~Node();
};

class RegExpr
{
public:
	RegExpr(Node* p = NULL);
	RegExpr& operator=(Node* p);

	std::string toString() const;
	NFAGraph getNFAGraph() const;

private:
	std::shared_ptr<Node> p;
};

class Char : public Node
{
public:
	Char(char _ch);
	virtual std::string toString() const override;
	virtual NFAGraph getNFAGraph() const override;
private:
	char _ch;
};

class AnyChar : public Node
{
public:
	virtual std::string toString() const override;
	virtual NFAGraph getNFAGraph() const override;
};

class Concat : public Node
{
public:
	Concat(const RegExpr& lhs, const RegExpr& rhs);
	virtual std::string toString() const override;
	virtual NFAGraph getNFAGraph() const override;
private:
	RegExpr lhs, rhs;
};

class Choose : public Node
{
public:
	Choose(const RegExpr& lhs, const RegExpr& rhs);
	virtual std::string toString() const override;
	virtual NFAGraph getNFAGraph() const override;
private:
	RegExpr lhs, rhs;
};

class StarClosure : public Node
{
public:
	StarClosure(const RegExpr& expr);
	virtual std::string toString() const override;
	virtual NFAGraph getNFAGraph() const override;
private:
	RegExpr expr;
};

class AddClosure : public Node
{
public:
	AddClosure(const RegExpr& expr);
	virtual std::string toString() const override;
	virtual NFAGraph getNFAGraph() const override;
private:
	RegExpr expr;
};