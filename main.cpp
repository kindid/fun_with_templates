#include <QCoreApplication>
#include <QTextStream>

#include <ptr.h>


// root man..
struct object
{ };

template<
    typename _parent>
struct
    inherits : _parent
{
    using _t_inherits = _parent;
};

////////////////////////////////////////////////////////////////

struct va : inherits<object>
{ };

struct vb : inherits<object>
{ };

struct vab : inherits<vb>
{ };

struct vabc : inherits<vab>
{ };

////////////////////////////////////////////////////////////////

template<typename ... _types> struct type_list
{
    using _t_list = type_list<_types...>;
};

template<
    typename _type,
    typename... _type_list>
struct append
    : type_list<_type_list..., _type>
{
    using _t_list = type_list<_type_list..., _type>;
};

template<
    typename _type,
    typename... _type_list>
struct prepend
    : type_list<_type_list..., _type>
{
    using _t_list = type_list<_type, _type_list...>;
};

////////////////////////////////////////////////////////////////

template<typename _type> struct find_parents;

template<> struct find_parents<object>
{
    using _t_parents = object;
};

template<typename _type> struct find_parents
{
    using _t_parents =
        typename type_list<
            _type,
            typename find_parents<
                typename _type::_t_inherits>
            ::_t_parents>
        ::_t_list;
};

////////////////////////////////////////////////////////////////

#include <sanitise.h>
#include <type_traits>
#include <typeinfo>

#define HACK(x) { s << '"' << #x << '"' << "\n" << sanitise(typeid(x).name()) << "\n"; }

int main(int /*argc*/, char * /*argv*/[])
{
    QTextStream s(stdout);

    HACK(int);
//    s << typeid(find_parents<vab>::_t_parents).name() << "\n";
//    s << typeid(type_list<int,void,int,vab,type_list<bool, float>>::_t_list).name() << "\n";
//    s << typeid(append<vab, type_list<int, void, bool>>::_t_list).name() << "\n";
    HACK(find_parents<vab>::_t_parents);
    HACK(find_parents<vabc>::_t_parents);
//    s << sanitise(typeid(find_parents<vabc>::_t_parents).name()) << "\n";
}
