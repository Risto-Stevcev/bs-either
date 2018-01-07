open BsMochajs.Mocha;
open BsJsverify.Verify.Arbitrary;
open BsJsverify.Verify.Property;
module Verify = BsAbstract.Verify;
type arbitrary('a) = BsJsverify.Verify.Arbitrary.arbitrary('a);
let (<.) = BsAbstract.Function.Infix.(<.);
let (const, id) = (BsAbstract.Function.const, BsAbstract.Function.Category.id);


let arb_either : (arbitrary('a), arbitrary('b)) => arbitrary(Either.either('a, 'b)) =
  (arb_left, arb_right) => {
    smap(
      e => switch e {
        | Types.Left(l) => Either.Left(l)
        | Types.Right(r) => Either.Right(r)
      },
      e => switch e {
        | Either.Left(l) => Types.Left(l)
        | Either.Right(r) => Types.Right(r)
      },
      ~newShow = a => switch a {
        | Either.Left(a') =>
          "Left("++ (Js.Json.stringifyAny(a') |> Js.Option.getWithDefault("")) ++")"
        | Either.Right(a') =>
          "Right("++ (Js.Json.stringifyAny(a') |> Js.Option.getWithDefault("")) ++")"
      },
      BsJsverify.Verify.Arbitrary.arb_either(arb_left, arb_right)
    )
  };

describe("Either", () => {
  describe("Medial Magma", () => {
    module Medial_Magma = 
      Either.Medial_Magma({type t = string}, BsAbstract.Int.Additive.Medial_Magma);
    module V = Verify.Medial_Magma(Medial_Magma);
    property4(
      "should satisfy bicommutativity",
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      V.bicommutativity
    )
  });

  describe("Semigroup", () => {
    module Semigroup = 
      Either.Semigroup({type t = string}, BsAbstract.Int.Additive.Semigroup);
    module V = Verify.Semigroup(Semigroup);
    property3(
      "should satisfy associativity",
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      V.associativity
    )
  });

  describe("Functor", () => {
    module V = Verify.Functor(Functors.String.Functor);
    property1("should satisfy identity", arb_either(arb_string, arb_nat), V.identity);
    property1(
      "should satisfy composition",
      arb_either(arb_string, arb_nat),
      V.composition((++)("!"), string_of_int)
    );
  });

  describe("Bifunctor", () => {
    module V = Verify.Bifunctor(Either.Bifunctor);
    property1(
      "should satisfy identity", arb_either(arb_string, arb_nat), V.identity
    );
    property1(
      "should satisfy composition",
      arb_either(arb_string, arb_nat),
      V.composition((++)("!"), (*.)(3.0), (++)("-"), float_of_int)
    );
  });

  describe("Apply", () => {
    module V = Verify.Apply(Functors.String.Apply);
    property1(
      "should satisfy associative composition",
      arb_either(arb_string, arb_nat),
      (n) =>
        V.associative_composition(
          Right((++)("!")), Right(string_of_int), n
        )
    )
  });

  describe("Applicative", () => {
    module V = Verify.Applicative(Functors.String.Applicative);
    property1("should satisfy identity", arb_either(arb_string, arb_nat), V.identity);
    property1(
      "should satisfy homomorphism",
      arb_either(arb_string, arb_nat),
      V.homomorphism(Functors.String.Functor.map(string_of_int))
    );
    property1(
      "should satisfy interchange",
      arb_nat,
      V.interchange(Right(string_of_int))
    );
  });

  describe("Monad", () => {
    module V = Verify.Monad(Functors.String.Monad);
    let pure = Functors.String.Applicative.pure;
    property1(
      "should satisfy associativity",
      arb_either(arb_string, arb_nat),
      V.associativity(pure <. string_of_int, pure <. (++)("!"))
    );
    property1(
      "should satisfy identity", arb_nat, V.identity(pure <. string_of_int)
    );
  });

  describe("Alt", () => {
    module V = Verify.Alt(Functors.String.Alt);
    property3(
      "should satisfy associativity",
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      V.associativity
    );
    property2(
      "should satisfy distributivity",
      arb_either(arb_string, arb_nat),
      arb_either(arb_string, arb_nat),
      V.distributivity(string_of_int)
    )
  });

  describe("Extend", () => {
    module V = Verify.Extend(Functors.Bool.Extend);
    property1(
      "should satisfy associativity",
      arb_either(arb_bool, arb_nat),
      V.associativity(
        Either.either(const(BsAbstract.String.Monoid.empty), string_of_float),
        Either.either(const(BsAbstract.Float.Additive.Monoid.empty), float_of_int)
      )
    );
  });

  describe("Show", () => {
    it("should show the either value", () => {
      expect(Functors.Int.Bool.Show.show(Either.Left(123))).to_be("123");
      expect(Functors.Int.Bool.Show.show(Either.Right(true))).to_be("true");
    })
  });

  describe("Eq", () => {
    it("should compare two either values for equality", () => {
      module E = Either.Eq(BsAbstract.Int.Eq, BsAbstract.Int.Eq);
      let eq = Functors.Int.Float.Eq.eq;
      expect(eq(Either.Left(123), Either.Left(123))).to_be(true);
      expect(eq(Either.Left(123), Either.Left(456))).to_be(false);
      expect(eq(Either.Right(12.3), Either.Right(12.3))).to_be(true);
      expect(eq(Either.Right(12.3), Either.Right(45.6))).to_be(false);
      expect(eq(Either.Left(123), Either.Right(45.6))).to_be(false);
      expect(E.eq(Either.Left(123), Either.Right(123))).to_be(false);
      expect(E.eq(Either.Right(123), Either.Left(123))).to_be(false);
    })
  });

  describe("Ord", () => {
    it("should compare two either values for equality", () => {
      module E = Either.Ord(BsAbstract.Int.Ord, BsAbstract.Int.Ord);
      let compare = Functors.Int.Float.Ord.compare;
      expect(compare(Either.Left(123), Either.Left(123))).to_be(`equal_to); 
      expect(compare(Either.Left(123), Either.Left(456))).to_be(`less_than);
      expect(compare(Either.Right(12.3), Either.Right(12.3))).to_be(`equal_to);
      expect(compare(Either.Right(12.3), Either.Right(45.6))).to_be(`less_than);
      expect(compare(Either.Left(123), Either.Right(45.6))).to_be(`less_than);
      expect(E.compare(Either.Left(123), Either.Right(123))).to_be(`less_than);
      expect(E.compare(Either.Right(123), Either.Left(123))).to_be(`greater_than);
    })
  });
});

