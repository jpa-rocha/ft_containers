/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:20:17 by jrocha            #+#    #+#             */
/*   Updated: 2023/02/07 15:27:51 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/include/vector.hpp"
# include <iostream>
# include <iomanip>
# include <string>
# include <iomanip>
# include <stdexcept>
# include <vector>
# include <stack>
# include <map>
# include <list>
# include <deque>
# include <limits>
# include <unistd.h>
# include <fcntl.h>
# include <cstring>
# include <sys/wait.h>
# include <sys/time.h>

class	B
	{
		public:
			char	*l;
			int		i;

			B() : l(NULL), i(1) {};
			B(const int &ex)
			{
				this->i = ex;
				this->l = new char('a');
			};
			virtual ~B()
			{
				delete this->l;
				this->l = NULL;
			};
	};

	class A : public B
	{
		public:
			A() : B() {};
			A(const B* ex)
			{
				this->l = new char(*(ex->l));
				this->i = ex->i;
				if (ex->i == -1) throw "n";
			}
			~A()
			{
				delete this->l;
				this->l = NULL;
			};
	};

int		main()
{
		ft::vector<int>		_vector;

		ft::vector<int>		tmp;
		tmp.assign(26000000, 1);
		_vector.assign(42000000, 1);

		_vector.insert(_vector.end() - 10000000, tmp.begin(), tmp.end());
	
		std::cout << (_vector[3]) << std::endl;
		std::cout << (_vector.size()) << std::endl;
		std::cout << (_vector.capacity()) << std::endl;

		/* std::unique_ptr<B> k2(new B(3));
		std::unique_ptr<B> k3(new B(4));
		std::unique_ptr<B> k4(new B(-1)); */
		B* k2 = new B(3);
		B* k3 = new B(4);
		B* k4 = new B(-1);

		ft::vector<A>	vv;
		ft::vector<B*>	v1;

		v1.push_back(&(*k2));
		v1.push_back(&(*k3));
		v1.push_back(&(*k4));
		
		try
		{
			vv.insert(vv.begin(), v1.begin(), v1.end());
		}
		catch (...)
		{
			std::cout << (vv.size()) << std::endl;
			std::cout << (vv.capacity()) << std::endl;
		}
		delete(k2);
		delete(k3);
		delete(k4);
		// ITERATORS TEST
		/* std::list<int> lst;
		std::list<int>::iterator lst_it;
		for (int i = 1; i < 5; ++i)
			lst.push_back(i * 3);

		ft::vector<int> vct(lst.begin(), lst.end());
		std::cout << vct.size() << std::endl;
		std::cout << vct.capacity() << std::endl;

		lst_it = lst.begin();
		for (int i = 1; lst_it != lst.end(); ++i)
			*lst_it++ = i * 5;
		vct.assign(lst.begin(), lst.end());
		std::cout << vct.size() << std::endl;
		std::cout << vct.capacity() << std::endl;

		vct.insert(vct.end(), lst.rbegin(), lst.rend());
		std::cout << vct.size() << std::endl;
		std::cout << vct.capacity() << std::endl; */
}
/* 5 5 1 58 58 1 58 58 58 1 10 8 1 1 58 58 1 58 58 58 1 30 8 10 10 10 9 4 4
5 5 1 58 58 1 58 58 58 1 8 8 1 1 58 58 1 58 58 58 1 30 8 10 10 10 0 0 4 5 */