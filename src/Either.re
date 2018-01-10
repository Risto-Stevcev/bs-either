open BsAbstract;
open BsAbstract.Interface;
let (flip, const) = BsAbstract.Function.(flip, const);

[@ocaml.deprecated "Use [Js.Result.t] type instead"]
type either('l, 'r) = Left('l) | Right('r);

let either: ('a => 'c, 'b => 'c, either('a, 'b)) => 'c = (f, g, a) => switch (f, g, a) {
  | (f, _, Left(a')) => f(a')
  | (_, g, Right(a')) => g(a')
  };

module Magma = (T: TYPE, M: MAGMA) => {
  module Either_Magma_: MAGMA with type t = either(T.t, M.t) = {
    type t = either(T.t, M.t);
    let append = (a, b) => switch (a, b) {
      | (Right(a'), Right(b')) => Right(M.append(a', b'))
      | (_, Right(b')) => Right(b')
      | (Right(a'), _) => Right(a')
      | (Left(a'), _) => Left(a')
      }
  };
  include Either_Magma_
};

module Medial_Magma = (T: TYPE, M: MAGMA) => {
  module Either_Medial_Magma_: MEDIAL_MAGMA with type t = either(T.t, M.t) = {
    include Magma(T, M);
  };
  include Either_Medial_Magma_
};

module Semigroup = (T: TYPE, S: SEMIGROUP) => {
  include Magma(T, S);
};

module Functor = (T: TYPE) => {
  module Either_Functor_: FUNCTOR with type t('a) = either(T.t, 'a) = {
    type t('a) = either(T.t, 'a);
    let map = (f, a) => switch a {
    | Left(l) => Left(l)
    | Right(r) => Right(f(r))
    }
  };
  include Either_Functor_
};

module Bifunctor: BIFUNCTOR with type t('a, 'b) = either('a, 'b) = {
  type t('a, 'b) = either('a, 'b);
  let bimap = (f, g, a) => switch a {
    | Left(a') => Left(f(a'))
    | Right(a') => Right(g(a'))
    }
};

module Apply = (T: TYPE) => {
  module Either_Apply_: APPLY with type t('a) = either(T.t, 'a) = {
    include Functor(T);
    let apply = (f, a) => switch (f, a) {
      | (Left(f'), _) => Left(f')
      | (Right(f'), a') => map(f', a')
      }
  };
  include Either_Apply_
};

module Applicative = (T: TYPE) => {
  module Either_Applicative_: APPLICATIVE with type t('a) = either(T.t, 'a) = {
    include Apply(T);
    let pure = a => Right(a)
  };
  include Either_Applicative_
};

module Monad = (T: TYPE) => {
  module Either_Monad_: MONAD with type t('a) = either(T.t, 'a) = {
    include Applicative(T);
    let flat_map = (a, f) => switch a {
      | Right(a') => f(a')
      | Left(a') => Left(a')
      };
  };
  include Either_Monad_
};

module Alt = (T: TYPE) => {
  module Either_Alt_: ALT with type t('a) = either(T.t, 'a) = {
    include Functor(T);
    let alt = (a, b) => switch (a, b) {
      | (Left(_), b') => b'
      | (a', _) => a'
      };
  };
  include Either_Alt_
};

module Extend = (T: TYPE) => {
  module Either_Extend_: EXTEND with type t('a) = either(T.t, 'a) = {
    include Monad(T);
    let extend = (f, a) => switch (f, a) {
      | (_, Left(a')) => Left(a')
      | (f', a') => Right(f'(a'))
      };
  };
  include Either_Extend_;
};

module Show = (Left: SHOW, Right: SHOW) => {
  module Either_Show_: SHOW with type t = either(Left.t, Right.t) = {
    type t = either(Left.t, Right.t);
    let show = either(Left.show, Right.show)
  };
  include Either_Show_
};

module Eq = (Left: EQ, Right: EQ) => {
  module Either_Eq_: EQ with type t = either(Left.t, Right.t) = {
    type t = either(Left.t, Right.t);
    let eq = (a, b) => switch (a, b) {
      | (Left(a'), Left(b')) => Left.eq(a', b')
      | (Right(a'), Right(b')) => Right.eq(a', b')
      | _ => false
      }
  };
  include Either_Eq_;
};

module Ord = (Left: ORD, Right: ORD) => {
  module Either_Ord_: ORD with type t = either(Left.t, Right.t) = {
    include Eq(Left, Right);
    let compare = (a, b) => switch (a, b) {
      | (Left(a'), Left(b')) => Left.compare(a', b')
      | (Right(a'), Right(b')) => Right.compare(a', b')
      | (Left(_), Right(_)) => `less_than
      | (Right(_), Left(_)) => `greater_than
      }
  };
  include Either_Ord_
};

module Bounded = (Left: BOUNDED, Right: BOUNDED) => {
  module Either_Bounded_: BOUNDED with type t = either(Left.t, Right.t) = {
    include Ord(Left, Right);
    let top = Right(Right.top);
    let bottom = Left(Left.bottom);
  };
  include Either_Bounded_
};

module Join_Semilattice = (Left: JOIN_SEMILATTICE, Right: JOIN_SEMILATTICE) => {
  module Either_Join_Semilattice_:
    JOIN_SEMILATTICE with type t = either(Left.t, Right.t) = {
    type t = either(Left.t, Right.t);
    let join = (a, b) => switch (a, b) {
      | (Left(a'), Left(b')) => Left(Left.join(a', b'))
      | (Right(a'), Right(b')) => Right(Right.join(a', b'))
      | (Right(a'), _) | (_, Right(a')) => Right(a')
      }
  };
  include Either_Join_Semilattice_
};

module Meet_Semilattice = (Left: MEET_SEMILATTICE, Right: MEET_SEMILATTICE) => {
  module Either_Meet_Semilattice_:
    MEET_SEMILATTICE with type t = either(Left.t, Right.t) = {
    type t = either(Left.t, Right.t);
    let meet = (a, b) => switch (a, b) {
      | (Left(a'), Left(b')) => Left(Left.meet(a', b'))
      | (Right(a'), Right(b')) => Right(Right.meet(a', b'))
      | (Left(a'), _) | (_, Left(a')) => Left(a')
      }
  };
  include Either_Meet_Semilattice_
};

module Bounded_Join_Semilattice =
  (Left: BOUNDED_JOIN_SEMILATTICE, Right: BOUNDED_JOIN_SEMILATTICE) => {
  module Either_Bounded_Join_Semilattice_:
    BOUNDED_JOIN_SEMILATTICE with type t = either(Left.t, Right.t) = {
    include Join_Semilattice(Left, Right);
    let bottom = Left(Left.bottom);
  };
  include Either_Bounded_Join_Semilattice_
};

module Bounded_Meet_Semilattice =
  (Left: BOUNDED_MEET_SEMILATTICE, Right: BOUNDED_MEET_SEMILATTICE) => {
  module Either_Bounded_Meet_Semilattice_:
    BOUNDED_MEET_SEMILATTICE with type t = either(Left.t, Right.t) = {
    include Meet_Semilattice(Left, Right);
    let top = Right(Right.top);
  };
  include Either_Bounded_Meet_Semilattice_
};

module Lattice = (Left: LATTICE, Right: LATTICE) => {
  include Join_Semilattice(Left, Right);
  include (
    Meet_Semilattice(Left, Right):
      (module type of Meet_Semilattice(Left, Right)) with type t := t
  );
};

module Bounded_Lattice = (Left: BOUNDED_LATTICE, Right: BOUNDED_LATTICE) => {
  include Bounded_Join_Semilattice(Left, Right);
  include (
    Bounded_Meet_Semilattice(Left, Right):
      (module type of Bounded_Meet_Semilattice(Left, Right)) with type t := t
  );
};

module Distributive_Lattice = (Left: LATTICE, Right: LATTICE) => {
  include Lattice(Left, Right);
};

module Bounded_Distributive_Lattice = (Left: BOUNDED_LATTICE, Right: BOUNDED_LATTICE) => {
  include Bounded_Lattice(Left, Right);
};

module Heyting_Algebra = (Left: HEYTING_ALGEBRA, Right: HEYTING_ALGEBRA) => {
  include Ord(Left, Right);
  include (
    Bounded_Distributive_Lattice(Left, Right):
      (module type of Bounded_Distributive_Lattice(Left, Right)) with type t := t
  );
  let not = either(l => Left(Left.not(l)), r => Right(Right.not(r)))
};

module Involutive_Heyting_Algebra =
  (Left: INVOLUTIVE_HEYTING_ALGEBRA, Right: INVOLUTIVE_HEYTING_ALGEBRA) => {
  include Heyting_Algebra(Left, Right);
};

module Boolean_Algebra =
  (Left: BOOLEAN_ALGEBRA, Right: BOOLEAN_ALGEBRA) => {
  include Heyting_Algebra(Left, Right);
};

module Semiring = (T: TYPE, S: SEMIRING) => {
  module A = Apply(T);
  module I = Infix.Apply(A);
  module Either_Semiring_: SEMIRING with type t = either(T.t, S.t) = {
    type t = either(T.t, S.t);
    let one = Right(S.one);
    let zero = Right(S.zero);
    let multiply = (a, b) => I.(S.multiply <$> a <*> b);
    let add = (a, b) => I.(S.add <$> a <*> b)
  };
  include Either_Semiring_ 
};

module Foldable = (T: TYPE) => {
  module Either_Foldable_: FOLDABLE with type t('a) = either(T.t, 'a) = {
    type t('a) = either(T.t, 'a);
    let fold_left = (f, initial, a) => switch a {
      | Left(_) => initial
      | Right(a') => f(initial, a')
      };
    let fold_right = (f, initial, a) => switch a {
      | Left(_) => initial
      | Right(a') => f(a', initial)
      };
    module Fold_Map = (M: MONOID) => {
      let fold_map = (f, a) => switch a {
        | Left(_) => M.empty
        | Right(a') => f(a')
        }
    };
    module Fold_Map_Plus = (P: PLUS) => {
      let fold_map = (f, a) => switch a {
        | Left(_) => P.empty
        | Right(a') => f(a')
        }
    };
    module Fold_Map_Any = (M: MONOID_ANY) => {
      let fold_map = (f, a) => switch a {
        | Left(_) => M.empty
        | Right(a') => f(a')
        }
    };
  };
  include Either_Foldable_
};

module Bifoldable: BIFOLDABLE with type t('a, 'b) = either('a, 'b) = {
  type t('a, 'b) = either('a, 'b);
  let bifold_left = (f, g, initial, a) => switch a {
    | Left(a') => f(initial, a')
    | Right(a') => g(initial, a')
    };
  let bifold_right = (f, g, initial, a) => switch a {
    | Left(a') => f(a', initial)
    | Right(a') => g(a', initial)
    };
  module Fold_Map = (M: MONOID) => {
    let fold_map = either
  };
  module Fold_Map_Any = (M: MONOID_ANY) => {
    let fold_map = either 
  };
  module Fold_Map_Plus = (P: PLUS) => {
    let fold_map = either 
  };
};

module Traversable = (T: TYPE, A: APPLICATIVE) => {
  module I = Infix.Apply(A);
  module E = Applicative(T);
  module Either_Traversable_: TRAVERSABLE with type t('a) = either(T.t, 'a) = {
    type t('a) = either(T.t, 'a);
    type applicative_t('a) = A.t('a);
    include (Functor(T): FUNCTOR with type t('a) := t('a));
    include (Foldable(T): FOLDABLE with type t('a) := t('a));

    let traverse = (f, a) => switch a {
      | Left(a') => A.pure(Left(a'))
      | Right(a') => A.map(E.pure, f(a'))
      };
    let sequence = a => switch a {
      | Left(a') => A.pure(Left(a'))
      | Right(a') => A.map(E.pure, a')
      };
  };
  include Either_Traversable_;
};

module Bitraversable = (A: APPLICATIVE) => {
  module I = Infix.Apply(A);
  module Either_Bitraversable_: BITRAVERSABLE
    with type applicative_t('a) = A.t('a) and type t('a, 'b) = either('a, 'b) = {
    type t('a, 'b) = either('a, 'b);
    type applicative_t('a) = A.t('a);
    include (Bifunctor: BIFUNCTOR with type t('a, 'b) := t('a, 'b));
    include (Bifoldable: BIFOLDABLE with type t('a, 'b) := t('a, 'b));

    let bitraverse = (f, g, a) => switch a {
      | Left(a') => A.map(x => Left(x), f(a'))
      | Right(a') => A.map(x => Right(x), g(a'))
      };
    let bisequence = a => switch a {
      | Left(a') => A.map(x => Left(x), a')
      | Right(a') => A.map(x => Right(x), a')
      };
  };
  include Either_Bitraversable_
};

module Infix = {
  include Infix.Bifunctor(Bifunctor);
};

module Choose = (A: ALT) => {
  let choose: (A.t('a), A.t('b)) => A.t(either('a, 'b)) =
    (a, b) => A.alt(A.map(x => Left(x), a), A.map(x => Right(x), b))
};

module Unsafe = {
  let from_left = a => switch a {
    | Left(a') => a'
    | _ => Js.Exn.raiseTypeError("You passed in a `Right` value to `from_left`")
    };
  let from_right = a => switch a {
    | Right(a') => a'
    | _ => Js.Exn.raiseTypeError("You passed in a `Left` value to `from_right`")
    };
};

let is_left = a => either(const(true), const(false))(a);
let is_right = a => either(const(false), const(true))(a);

let note: ('a, option('b)) => either('a, 'b) =
  default => BsAbstract.Option.maybe(~f=x => Right(x), ~default=Left(default));

let hush: either('a, 'b) => option('b) =
  e => either(const(None), BsAbstract.Option.Applicative.pure)(e);
