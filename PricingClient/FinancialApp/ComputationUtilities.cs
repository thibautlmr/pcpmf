using GrpcPricing.Protos;
using MarketData;
using ParameterInfo.RebalancingOracleDescriptions;
using TimeHandler;
namespace FinancialApp
{
    public class ComputationUtilities
    {
        public PricingOutput PricingOutput { get; set; }
        public DataUtilities DataUtilities { get; set; }

        public ComputationUtilities(PricingOutput pricingOutput, DataUtilities dataUtilities)
        {
            PricingOutput = pricingOutput;
            DataUtilities = dataUtilities;
        }

        public bool RebalancingTime(int t)
        {
            IRebalancingOracleDescription rebalancingOracleDescription = DataUtilities.TestParameters.RebalancingOracleDescription;
            if (rebalancingOracleDescription.Type == RebalancingOracleType.Fixed)
            {
                int period = ((FixedTimesOracleDescription)rebalancingOracleDescription).Period;
                return t % period == 0;
            }
            else
            {
                throw new InvalidDataException("Invalid Rebalancing Description");
            }
        }

        public double GetFreeRateBetweenTwoDates(DateTime date1, DateTime date2)
        {
            string domesticCurrencyId = DataUtilities.TestParameters.AssetDescription.DomesticCurrencyId;
            double annualFreeRate = DataUtilities.TestParameters.AssetDescription.CurrencyRates[domesticCurrencyId];
            int numberOfDaysInOneYear = DataUtilities.TestParameters.NumberOfDaysInOneYear;
            MathDateConverter mathDateConverter = new(numberOfDaysInOneYear);
            double elapsedTime = mathDateConverter.ConvertToMathDistance(date1, date2);
            return annualFreeRate * elapsedTime / numberOfDaysInOneYear;
        }

        public double[] GetDeltas()
        {
            return PricingOutput.Deltas.ToArray();
        }

        public double[] GetDeltaStdDev()
        {
            return PricingOutput.DeltasStdDev.ToArray();

        }

        public double GetPrice()
        {
            return PricingOutput.Price;
        }

        public double GetPriceStdDev()
        {
            return PricingOutput.PriceStdDev;
        }

        public bool IsMonitoringDateReached(DateTime date)
        {
            DateTime[] paymentDates = DataUtilities.TestParameters.PayoffDescription.PaymentDates;
            for (int i = 0; i < paymentDates.Length; i++)
            {
                if (paymentDates[i].Date == date)
                {
                    return true;
                }
            }
            return false;
        }

        public double GetElapsedTime(DateTime date)
        {
            int numberOfDaysInOneYear = DataUtilities.TestParameters.NumberOfDaysInOneYear;
            DateTime firstDate = DataUtilities.MarketData[0].Date;
            MathDateConverter mathDateConverter = new(numberOfDaysInOneYear);
            return mathDateConverter.ConvertToMathDistance(firstDate, date);
        }
    }
}
